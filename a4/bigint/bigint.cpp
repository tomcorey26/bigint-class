//
// Started by Tom on 2/9/18.
//

#include "bigint.h"

//takes out un needed zeros from number
void bigint::strip_zeros() {
  int i = number.size()-1;
  if (number.size() > 1){
    while (number[i]==0 && number.size()>1){
      number.pop_back();
      i--;
    }
  }
}

/* Constructors
 *
 * */

//base constructor
bigint::bigint() {
  number.push_back(0);
  strip_zeros();
}

//allows for big ints to be established as a vector
bigint::bigint(const std::vector<vec_bin> &that) {
  number = that;
  strip_zeros();

}

//creates big int from integer
bigint::bigint(unsigned long long i) {
  number.clear();
  if (i==0){
    number.push_back(0);
  }
  while (i != 0){
    int end = i % 10;
    number.push_back((vec_bin)end);
    i = i / 10;
  }
strip_zeros();
}
/*
"1234"
'4'
(int)('4' - '0')

*/

//creates bigint from integer
bigint::bigint(std::string str) {
  number.clear();
  for (int i = str.length() - 1; i >= 0;i--){
    number.push_back((vec_bin)(str[i] - '0'));
  }
 strip_zeros();
}

//writes big int to file
bigint::bigint(std::ifstream &infile) {

  if (!infile.fail()) {
      std::string line;
      std::string fulltext;
      while (getline(infile,line)){
        fulltext += line;
      }
      infile.close();

      *this = fulltext;
      strip_zeros();

    }
		// if file isnt found give error message
		else {
					std::cerr << "Cant open file " << "\n";
			}
}

//yeilds two equivalent big ints
bigint::bigint(const bigint &that) {
  number = that.getNumber();
  strip_zeros();
}


/* Number Access
 *
 * */

//returns big int
const std::vector<vec_bin> &bigint::getNumber() const {
    return number;
}

//makes it so you can get an index of a big int
vec_bin bigint::operator[](size_t index) const {
  return number[index];
}

/** Comparators
 *
 * */

// allows big int to be compared as equal
bool bigint::operator==(const bigint &that) const {
  return (number == that.number);

}

// allows big int to be compared as unequal
bool bigint::operator!=(const bigint &that) const {
  return (number != that.number);
}

bool bigint::operator<(const bigint &that) const {

  if (number.size() > that.number.size()){
    return false;
  }
  else if (number.size() < that.number.size()){
    return true;
  }
  else if (number.size() == that.number.size()){
    int index = number.size()-1;
    while (index >= 0){
      if (number[index] > that.number[index]){
        return false;
      }
      else if  (number[index] < that.number[index]){
        return true;
      }
      else{
        index--;
      }
    }
  }
  return false;
}

bool bigint::operator<=(const bigint &that) const {
  return(number < that.number || number == that.number);
}

bool bigint::operator>(const bigint &that) const {
  if (number.size() > that.number.size()){
    return true;
  }
  else if (number.size() < that.number.size()){
    return false;
  }
  else if (number.size() == that.number.size()){
    int index = number.size()-1;
    while (index >= 0){
      if (number[index] > that.number[index]){
        return true;
      }
      else if  (number[index] < that.number[index]){
        return false;
      }
      else{
        index--;
      }
    }
  }
  return false;
}

bool bigint::operator>=(const bigint &that) const {
  return(number > that.number || number == that.number);
}


/** Addition
 *
 * */


bigint bigint::add(const bigint &that) const {

  int carry = 0;

  //vector of completed addition
  std::vector <vec_bin> num;

  //vectors of this and that
  std::vector <vec_bin> bigint1 = number;
  std::vector <vec_bin> bigint2 = that.number;

  //determine which vector is biggest
  unsigned biggest = (bigint1.size() >= bigint2.size() ? bigint1.size() : bigint2.size());

  for(unsigned i=0; i < biggest;i++){

    // when one num < other , add zeros so addition can still be done
    if (i > bigint1.size()-1){
      bigint1.push_back(0);
    }
    if(i > bigint2.size()-1){
      bigint2.push_back(0);
    }

    int num1 = bigint1[i];
    int num2 = bigint2[i];

    //find sum of two numbers
    int sum = num1 + num2 + carry;

    //push back the remainder of the sum
    num.push_back(sum % 10);

    //get the carry by dividing sum by 10
    carry = sum/10;
}
  if (carry == 1){
    num.push_back(1);
  }
  bigint finalnum = num;
  return finalnum;
}

bigint bigint::operator+(const bigint &that) const{
  return(this->add(that));
}

bigint &bigint::operator+=(const bigint &that) {
  *this = *this + that;
  return(*this);
}

bigint &bigint::operator++() {
  *this = *this + 1;
  return(*this);
}

bigint bigint::operator++(int) {
  *this = *this + 1;
  return(*this);

}


/** Subtraction
 *
 * */

bigint bigint::subtract(const bigint &that) const {

  //have some sort of error message if second number is bigger than first
  if (number < that.number){
    std::cerr << "First number must be bigger than second" << std::endl;
  }

  //vector of completed subtraction
  std::vector <vec_bin> num;

  //vectors of this and that
  std::vector <vec_bin> bigint1 = number;
  std::vector <vec_bin> bigint2 = that.number;

  //set carry to zero
  int carry = 0;

  //loop the size of this*
  for(unsigned i=0; i < bigint1.size();i++){

    // when one num < other , add zeros so subtraction can still be done
    if (i > bigint2.size()-1){
      bigint2.push_back(0);
    }

    int num1 = bigint1[i];
    int num2 = bigint2[i];

    //sum equals this - that + carry
    int sum = num1 - num2 + carry;

    //if sum is less than zero add 10 to sum and make carry = -1
    if (sum < 0){
      sum += 10;
      carry = -1;
    }
    else {
      carry =0;
    }

    //append subtracted number to num
    num.push_back(sum);
}
  bigint finalnum = num;
  return finalnum;


}



bigint bigint::operator-(const bigint &that) const {
  return(this->subtract(that));
}

bigint &bigint::operator-=(const bigint &that) {
  *this = *this - that;
  return(*this);
}

bigint &bigint::operator--() {
  *this = *this -1;
  return(*this);
}

bigint bigint::operator--(int) {
  *this = *this -1;
  return(*this);
}


/** Multiplication
 *
 * */

bigint bigint::multiply(const bigint &that) const {
  //vector of completed multiplication
  std::vector <vec_bin> biggest = number;
  std::vector <vec_bin> smallest = that.number;

  //bigint to add the number to
  bigint vecAdd;

  //if one bigint is bigger than the other than swap
  if (smallest.size() > biggest.size()){
    biggest = that.number;
    smallest = number;
  }

  //for loop smallest times and add the biggest to a total every time
  bigint i = 0;
  while (i < smallest){
    vecAdd = vecAdd + biggest;
    i++;

  }

    return vecAdd;
  }




bigint bigint::operator*(const bigint &that) const {
  return(this->multiply(that));
}

bigint &bigint::operator*=(const bigint &that) {
  *this = *this * that;
  return(*this);

}


/** Division
 *
 * */

bigint bigint::divide(const bigint &that) const {


  bigint numerator = number;
  bigint denom = that.number;
  bigint finish;

  //when the numerator is more then dividen just return 0
  if (numerator < denom){
    return finish;
  }
  //if they are equal to each other return 1
  else if (numerator == denom){
    finish++;
    return finish;
  }
  else {
  bigint total = 0;
  while (total < numerator){
    if ((numerator - total) < denom){
      return finish;
    }
    total += denom;
    finish++;
  }
}
  return finish;
}




bigint bigint::operator/(const bigint &that) const {
  return(this->divide(that));
}

bigint &bigint::operator/=(const bigint &that) {
  *this = *this / that;
  return(*this);
}


/** Modulo
 *
 * */

//essentially the same exact thing as division except you return remainder
bigint bigint::mod(const bigint &that) const {

  bigint numerator = number;
  bigint denom = that.number;
  bigint rem;

  //when the numerator is the same as denom return 0
  if (numerator == denom){
    return rem;
  }
  //if the numerator is less than denom just return numer
  else if (numerator < denom){
    return numerator;
  }
  else {
  bigint total = 0;
  bigint remain;
  while (total < numerator){
    if ((numerator - total) < denom){
      rem = numerator - total;
      return rem;
    }
    total += denom;
  }
}
  return rem;
}

bigint bigint::operator%(const bigint &that) const {
  return(this->mod(that));
}

bigint &bigint::operator%=(const bigint &that) {
  *this = *this % that;
  return(*this);
}


/** Power
 *
 * */

bigint bigint::pow(unsigned long long n) {
  bigint num = number;

  if (n == 0){
    num = {1};
    return num;
  }
  else if (n==1){
    return num;
  }
  else {
  bigint total = 1;
  for (unsigned int i=0;i < n;i++){
    total *= num;

  }
  num = total;
}
  return num;
 }


/** Display methods
 *
 * */

std::ostream &operator<<(std::ostream &os, const bigint &bigint1) {
  os << bigint1.to_string(true);
  return(os);
}



//converts bigint to string
std::string bigint::to_string(bool commas) const {
  std::string str;
  for (unsigned i = number.size();i > 0;i--){
    std::string numStr = std::to_string(number[i-1]);
    if (commas == true){
      if (i % 3 == 0 && i != number.size()){
        str += ",";
      }
    }
    str += numStr;

  }
  return str;
}
//

//converts bigint to scienctific notation
std::string bigint::scientific(unsigned int decimal_points) const {
  std::string str;

  //if the someone inputs different decimal
  unsigned int decimal = 3;
  if (decimal_points != decimal){
    decimal = decimal_points;
  }

  //make string of number
  unsigned int count = 0;
  unsigned int size = number.size();

  //while the number is less than decimal parameter
  while(count < decimal+1) {

    //add number to string
    if (count < number.size()){
      std::string numStr = std::to_string(number[size-1]);
      str += numStr;
      size--;
    }
    //add zero if number isnt long enough for requested decimal
    else {
      str.append("0");
    }

    count++;

  }

  str.insert(1,".");
  str.append("E");
  str.append(std::to_string(number.size()-1));

  return str;

}

//writes big int to file
void bigint::to_file(std::ofstream &outfile, unsigned int wrap) {
  if (outfile.is_open()){
    std::string str;
    int counter = 0;
    for (int i = number.size();i > 0;i--){
      std::string numStr = std::to_string(number[i-1]);
      str += numStr;
      counter++;
      if (counter % wrap == 0){
        str+= "/n";
      }
    }
    outfile << str;
    outfile.close();
  }

}
