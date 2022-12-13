#include <iostream>
using namespace std;

int binary_chk(string a){
    int b = a.length();
    int flag = 0;
    for(int i=0; i<b; i++)
        if(a[i] != '0' && a[i] != '1')
            flag = 1;
    return flag;
}

// XOR for modulo2 division
string xor1(string a, string b)
{
    string str = "";
    int n = b.length();
    for(int i=1; i<n; i++){
        if(a[i] == b[i])
            str += "0";
        else
            str += "1";
    }
    return str;
}

string mod2div(string msg, string key){

    int mlen = msg.length();
    int klen = key.length();
    string temp = msg.substr(0, klen);
    while(klen < mlen){
        if(temp[0] == '1')
            temp = xor1(temp,key)+ msg[klen]; 
        else
            temp = xor1(string(klen, '0'), temp) + msg[klen];
        klen += 1;
    }

    //after last iteration, XOR of remaining bits
    if(temp[0] == '1')
        temp = xor1(temp, key);
    else
        temp = xor1(string(klen,'0'), temp);

    return temp;
}

string sender(string msg, string key){

    cout << "Your Message : " << msg << endl;
    cout << "Your Key : " << key << endl;
    int klen = key.length()-1;
    string nmsg = msg+string(klen, '0');

    string remainder = mod2div(nmsg, key);
    cout << "Message sent : " << msg+remainder << endl << endl;
    return msg+remainder;   // returns msg+remainder
}
void receiver(string msg, string key){
    cout << "Received Message : " << msg << endl;
    cout << "Key : " << key << endl;
    cout << "Checking Received Message..." << endl;
    string check = mod2div(msg, key);

    int klen = key.length()-1;
    if(check == string(klen, '0'))
        cout << "Message Succesfully Received :)" << endl;
    else
        cout << "There is some data Lost :(" << endl;

}
int main()
{
    string msg;
    string key;
    label:
    cout << "Enter the data to send (In Binary) : ";
    cin >> msg;
    if(binary_chk(msg) == 1){
        cout << "Msg is not Binary (0's or 1's) :("<< endl;
        goto label;
    }
    label1:
    cout << "Enter a key (In Binary) : ";
    cin >> key;
    if(binary_chk(key) == 1){
        cout << "Key is not Binary (0's or 1's) :(" << endl;
        goto label1;
    }
    string msgR = sender(msg, key);
    receiver(msgR, key);
    return 0;
}


