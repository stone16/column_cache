#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>

int getIndex_b(int a);
int getIndex_f(int a);
int getTag_Hi(int a);
int getRbit(int a);
void swap(int a,int b);

int main() {
    std::string line;
    std::vector<long int> v;
    std::ifstream myfile;
// input the address stream
    myfile.open("/Users/apple/Desktop/trace_k.txt",std::ios::in);
    long int a;
    // open the file and change it into integers

    if (myfile.is_open()){
        while(getline(myfile,line)){
            line = line.substr(3);

            char *str2=const_cast<char*>(line.c_str());
            sscanf(str2,"%lx",&a);
            v.push_back(a);
        }
    }else{
        std::cout<< " the file is not there! " << std::endl;
    }
    std::cout<<"  done     " << v.size()<<std::endl << std::endl;
//  5 offset; 8 index; 19 tag

    int index = 0;
    int hit = 0;
    int miss = 0;
// all the rbits are 1 at the very beginning
    //table contains three part, tag, highest bit in index and rbit
    int table[256]={1};

    for (int i = 0; i < v.size(); ++i) {
        //judge if tag is same
        if (((table[getIndex_b(v.at(i))])>>2)== ((getTag_Hi(v.at(i)))>>1)){
            hit++;
        }else{
            if(getRbit(table[getIndex_b(v.at(i))])==1){
                //store the tag and the highest index in corresponding table, rbit = 0
                table[getIndex_b(v.at(i))] = getTag_Hi(v.at(i))<<1;
                miss++;
            }else{
                if (((table[getIndex_f(v.at(i))])>>1)== ((getTag_Hi(v.at(i))))){
                    swap(table[getIndex_f(v.at(i))],table[getIndex_b(v.at(i))]);
                    hit++;
                }else{
                    table[getIndex_f(v.at(i))] = (getTag_Hi(v.at(i))<<1)+1;
                    swap(table[getIndex_f(v.at(i))],table[getIndex_b(v.at(i))]);
                    miss++;
                }


            }

        }
    }

std::cout << "Hit is " << hit << ", miss is "<< miss << std::endl<<"The miss rate is " << ((float)miss/v.size()) << std::endl;
    return 0;
}




//get index
int getIndex_b(int a){

    return (a&(256<<5))>>5;
}

//get index and invert the highest bit
int getIndex_f(int a){

    return ((~(a&(1<<12)))+(a&(128<<5)))>>5;
}


int getTag_Hi(int a){
    //get tag and the highest bit in index part
    return a>>12;
}


int getRbit(int a){
    return a&1;
}

void swap(int a,int b){
    int temp = 0;
    temp =a;
    a = b;
    b = temp;
}
