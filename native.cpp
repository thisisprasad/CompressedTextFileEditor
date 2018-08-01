//#include "main.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//#include<iostream>
//#include<stdio.h>
//#include<conio.h>
//#include"compHeader.hpp"
//using namespace std;
//
//void initCompress()
//{
//    cout<<"Inside the initCompress() function"<<endl;
//    solve();
//    //  main();
//}


///////////////////////////////////////////////////////////////////////////////////////////////////////
/**
    One observation:
    -The tree created by decoder and encoder are different and hence the decoded file is not same
     original.
**/

//  working with the overloaded operators

/*
    This is a header file for Huffman encoder and decoder
*/

/**
    This file has all the templates of the class.
    We have to define all the functions(subroutines) of the class.
**/
#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<fstream>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<cstdio>
#include<algorithm>
#include<string.h>
#include<cstring>
#include<string>
#include<string.h>

using namespace std;


class HuffmanNode
{
public:
    char symbol;
    unsigned long codeword, freq;
    unsigned short runLen, codewordLen;
    HuffmanNode *left, *right;

    HuffmanNode(char s, unsigned long f, unsigned int r, HuffmanNode *lt = 0, HuffmanNode *rt = 0)
    {
        symbol = s;
        freq = f;
        runLen = r;
        left = lt;
        right = rt;
//  Left and right pointers point to NULL(0)
    }
};

class ListNode
{
public:
    HuffmanNode *tree;
    ListNode *prev, *next;

    ListNode()
    {
        next = 0;
        prev = 0;
    }

    ListNode(ListNode *p, ListNode *n)
    {
        prev = p;
        next = n;
    }
};

class DataRec
{
public:
    char symbol;
    unsigned long freq;
    unsigned short runLen;

    DataRec(){}     //  default constructor overriden

    bool operator==(DataRec &dr) const    //  Used to check equality when using find()
    {
        return (symbol == dr.symbol && runLen == dr.runLen);
    }

    bool operator<(DataRec &dr) const   //  used for sort() function of STL.
    {
        return (freq < dr.freq);
    }
};

class HuffmanCoding
{
public:
    HuffmanCoding() : mask(0xff), bytes(4), bits(8), ASCII(256) //  These are const
    {
        chars = new HuffmanNode*[ASCII + 1];    //  257 locations(0 to 256) are allocated
    }

    void compress(char *, ifstream &);
    void decompress(char *, ifstream &);
//  The above two functions touch the file or the file can communicate with them directly while execution  of the appluication

private:
    const unsigned int bytes, bits, ASCII;
    const unsigned long mask;
    unsigned short dataSize;
    unsigned long charCnt;
    ofstream fout;
    HuffmanNode *HuffmanTree, **chars;
    vector<DataRec> data;   //  This is the table
    void error(string s)
    {
        cerr<<s<<endl;
        cout<<"\n\tExiting the application"<<endl;
        exit(10);
    }

//  Member functions
//  public:
    void output(unsigned long pack);
    void garnerData(ifstream &);
    void outputFrequencies(ifstream &);
    void read2ByteNum(unsigned short &, ifstream &);  //  reamining
    void read4ByteNum(unsigned long &, ifstream &); //  remaining
    void inputFrequencies(ifstream &);  //  remaining
    void createHuffmanTree();
    void createCodewords(HuffmanNode *, unsigned long, int);
    //  void transformTreeToArrayOfLists(HuffmanNode *);
    void treeToArrayLists(HuffmanNode *);
    void encode(ifstream &);
    void decode(ifstream &);


//  Debugging functions below///////////////////////////////////////
    void checkBits(unsigned long &);    //  Debugging for the pack contents

};

void HuffmanCoding::garnerData(ifstream &fin)
{
    char ch, ch2;
    DataRec r, temp;  //  This is our priority queue
    r.freq = 1;

    vector <DataRec>::iterator i;
    //r.freq=1;

    for(fin.get(ch); !fin.eof();ch=ch2 )
    {
        for(r.runLen = 1, fin.get(ch2); !fin.eof() && ch == ch2; r.runLen++)    //  This loop runs only once for symbols having runLength = 1
        {
            fin.get(ch2);
            ////getch();
        }

        r.symbol = ch;

    //  STL find() is not working, so find is implemented using a loop.
        int j;
        for(j = 0; j < data.size(); j++)
            if(data[j].symbol == r.symbol && data[j].runLen == r.runLen)    //  The corresponding symbol with appropriate runLength is found
                break;
        if(j != data.size())
            data[j].freq += 1;  //  Increase its frequency by one
        else    //  Till now we have not encountered the symbol with the calculated runLength
            data.push_back(r);  //  Add it to the table.
    }

    sort(data.begin(), data.end()); //  Sort it according to the frequency


/** Displaying the table **/
    cout<<"\n\tDisplaying the table"<<endl;
    for(int k = 0; k < data.size(); k++)
        cout<<data[k].symbol<<" "<<data[k].runLen<<" "<<data[k].freq<< " "<<endl;
}

void HuffmanCoding::output(unsigned long pack)
{
    char *s = new char[bytes];

    for(int i = bytes -1; i >= 0; i--)
    {
        s[i] = pack & mask;
        pack = pack >> bits;    //  Move the pack bits to right by 8 bits
    }

    //  Write the contents of the pack into the file
    for(int i = 0 ; i < bytes; i++)
        fout.put(s[i]);
}

void HuffmanCoding::treeToArrayLists(HuffmanNode *p)
{
/**
    If p is leaf node we include it in the linked list associated with that symbol
**/
    if(p->left == NULL && p->right == NULL) //  Obeys sibling property so if one of the side is pointing to NULL it means it is a leaf node
    {
        p->right = chars[(unsigned char)p->symbol];
        chars[(unsigned char)p->symbol] = p;    //  points to 'p'
    }
    else
    {
        treeToArrayLists(p->left);
        treeToArrayLists(p->right);
    }
}

void HuffmanCoding::compress(char *inFileName, ifstream &fin)
{
    char outFileName[1000];
    //  strcat(inFileName, ".en");
    strcpy(outFileName, inFileName);
    strcat(outFileName, ".en");



    fout.open(outFileName, ios::out | ios::binary);

    garnerData(fin);    //  Creates the table which stores the frequecies and runLength. ->Working fine!!
    outputFrequencies(fin);

    createHuffmanTree();
    createCodewords(HuffmanTree, 0, 0);

    //  memset(chars, NULL, sizeof(chars)); //  If this statement doesn't work then use a loop
    for(int i = 0; i <= ASCII; i++)
        chars[i] = NULL;

    treeToArrayLists(HuffmanTree);

////////////////////////////////////////////////////////////////////////////////////////////
    //  //getch();
    cout<<"\nPrinting the chars array:- "<<endl;
    for(int i = 0; i < 256; i++)
    {
        HuffmanNode *p;
        for(p = chars[i]; p != NULL; p = p->right)
            cout<<p->symbol<<" "<<p->runLen<<" "<<p->freq<<" "<<"Ascii-value: "<<i<<endl;
    }
    //  //getch();
////////////////////////////////////////////////////////////////////////////////////////

    fin.clear();
    fin.seekg(0, ios::beg); //  Move the input file pointer to the begining

    encode(fin);    //  Writes the bitwise information of each character in the output file

    cout<<"\n\tWrite code for compression details"<<endl;

    fout.close();
}

void HuffmanCoding::encode(ifstream &fin)
{
    int check = 0;
    unsigned long packCount, hold, packSize = bytes*bits, pack;
    packCount = 0;
    pack = 0;   //  Initially all bits are zero
    short bitsLeft, rlength;
    char ch, ch2;
    HuffmanNode *p;

//  Read the whole file.
    for(fin.get(ch); !fin.eof();)
    {
        //  cout<<"Read form File: "<<ch<<endl;
        //  //getch();
        for(rlength = 1, fin.get(ch2); !fin.eof() && ch == ch2; rlength++)  //  Calculate the runlength of a partivulare symbol
        {
            fin.get(ch2);
            //  cout<<"Read form File: "<<ch2<<endl;
            //  //getch();
        }

        for(p = chars[(unsigned char) ch]; p != NULL && p->runLen != rlength; p = p->right)
            ;
        //  cout<<"chars loop of encode: "<<p->symbol<<" "<<p->runLen<<" "<<p->codewordLen<<endl;
        //  //getch();
        check++;
        if(p == NULL)
        {
            cout<<"\ncheck = "<<check<<endl;
            error("\n\tThere is problem in encode()");
        }
        //  cout<<"\ncheck = "<<check<<endl;

        if(p->codewordLen < (packSize - packCount))
        {
        /**
            There are enough bits in pack to store bits of p->symbol. So we just shift the pack bits to left by 'codewordLen'
            space and store the bits
        **/
            pack = pack << p->codewordLen;  //  shift left
            pack = pack | p->codeword;   //  store the codeword
            packCount += p->codewordLen;    //  increase the count
        }
        else
        {
        /**
            we store the MSBs that can be fitted into pack. Write it to the output file and then store the rest of the LSBs in pack
        **/
            bitsLeft = packSize - packCount;
            pack = pack << bitsLeft;

            if(bitsLeft != p->codewordLen)
            {
                int discard = p->codewordLen - bitsLeft;
                hold = p->codeword;
                hold = hold >> discard; //  only stores the required MSBs

                pack = pack | hold;
            }
            else
                pack = pack | p->codeword;


            //  cout<<"\n\tPack is in encode(): "<<pack<<endl;
            //  checkBits(pack);
            output(pack);   //  Write the contents in the file
            //  checkBits(pack);

            if(p->codewordLen != bitsLeft)
            {
                pack = 0;
                pack = p->codeword;
                packCount = packSize - (p->codewordLen - bitsLeft); //  Why do we even need this statement?
                packCount = (p->codewordLen - bitsLeft);
            /**
                Here we don't shift the MSBs written earlier in the pack. Rather, they would be overwritten as the count is handled properly
            **/
            }
            else packCount = 0;
        }

        ch = ch2;
    }

    if(packCount != 0)  //  Transfer the left over bits
    {
        //  checkBits(pack);
        pack = pack << (packSize - packCount);
        //  checkBits(pack);
        output(pack);
    }
}

void HuffmanCoding::outputFrequencies(ifstream &fin)
{
    unsigned long temp4;
    char ch = data.size();
    int sz = data.size();   //  Used for debugging
    unsigned short temp2 = data.size();
    temp2 =  temp2 >> bits;
    //  fout.put(ch);
    fout.put((temp2)).put(ch);
    //  fout.put(ch);
    fin.clear();
    output((unsigned long) fin.tellg());

    for(int i = 0; i < data.size(); i++)    //  Table is written into the file
    {
        fout.put(data[i].symbol);
        cout<<"\n\t"<<(char)data[i].symbol<<" is now written into the output file"<<endl;
        //  fout<<(char)data[i].symbol<<" is now written"<<endl;
        //  fout<<"Is this written into the file"<<endl; --->>> This is getting displayed, so the contents are being written into the file
        ch = temp2 = data[i].runLen;
        temp2 = data[i].runLen;
        temp2 = temp2 >> bits;
        //  fout.put(ch);
        fout.put((temp2)).put(ch);  //  runLen written into the file
        //  fout.put(ch);
        temp4 = data[i].freq;
        output(temp4);
    }

    cout<<"\n\tSize of the table in encode stage: "<<sz<<endl;  //  Used for debugging
}

void HuffmanCoding::read2ByteNum(unsigned short &num, ifstream &fin)
{
    num = fin.get();
    num <<= bits;   //  shift left by 8 bits
    num = num | fin.get();
}

void HuffmanCoding::read4ByteNum(unsigned long &num, ifstream &fin)
{
    num = (unsigned long)fin.get();
    for(int i = 0; i < 3; i++)
    {
        num <<= bits;
        num |= (unsigned long)fin.get();
    }
}

void HuffmanCoding::inputFrequencies(ifstream &fin)
{
    DataRec r;
    data.clear();
    read2ByteNum(dataSize, fin);
    int sz = dataSize;
    read4ByteNum(charCnt, fin);
    data.reserve(dataSize); //  Reserve enough memory having capacity dataSize

    for(int j = 0; !fin.eof() && j < dataSize; j++)
    {
        r.symbol = fin.get();
        read2ByteNum(r.runLen, fin);
        read4ByteNum(r.freq, fin);
//  The sequnce given above matters because, the info was written down in this manner a the time of encoding
        data.push_back(r);  //  Entry added in table
    }

    cout<<"\n\tSize of the table in decode stage: "<<sz<<endl;
    cout<<"\n\tcharCnt: "<<charCnt<<endl;
}

void HuffmanCoding::decode(ifstream& fin)
{

    unsigned long chars;
    char ch,bitCnt=1,mask=1;
    mask<<=bits-1;  //change 00000001 to 10000000;
    for(chars=0,fin.get(ch); !fin.eof() && chars<charCnt;)
    {
        for(HuffmanNode *p=HuffmanTree;;)
        {
            if(p->left==0 && p->right==0)   //  Leaf node found
            {
                for(int j=0;j<p->runLen;j++)
                    fout.put(p->symbol);
                chars+=p->runLen;
                break;

            }
            else if((ch&mask)==0)
                p=p->left;
            else
                p=p->right;
            if(bitCnt++== bits)
            {
                fin.get(ch);
                bitCnt=1;

            }
            else
                ch<<=1;
        }
    }

}
void HuffmanCoding::decompress(char *inFileName,ifstream& fin)
{
    char outFileName[30];
    strcpy(outFileName,inFileName);
    strcat(outFileName, ".dec");

    fout.open(outFileName,ios::out|ios::binary);
    inputFrequencies(fin);
    createHuffmanTree();
    createCodewords(HuffmanTree,0,0);
    decode(fin);

/** Displaying the table **/
    cout<<"\n\tDisplaying the table"<<endl;
    for(int k = 0; k < data.size(); k++)
        cout<<data[k].symbol<<" "<<data[k].runLen<<" "<<data[k].freq<< " "<<endl;

    fout.close();   //  The stream associated with the file is released.
}


void HuffmanCoding::createCodewords(HuffmanNode *p,unsigned long codeword,int len)
{
    if(p->left==0 && p->right==0)                                                         //for leaf node store codeword and its length
    {
        p->codeword = codeword;
        p->codewordLen = len;
        cout<<p->symbol<<endl;
    }
    else
    {
        if(p->left != NULL)
        {
            cout<<"0 ";
            createCodewords(p->left,codeword<<1,len+1);                          //for non-leaf nodes travel to the sides which are not null
        }
        if(p->right != NULL)
        {
            cout<<"1 ";
            createCodewords(p->right,(codeword<<1)+1,len+1);                     // << - shifts binary code by 1 bit to left which
        }
                                                                                            // creates 0 at lsb and 1 is added to travel on right
    }
}


void HuffmanCoding::createHuffmanTree()
{
    ListNode *p,*newNode,*head,*tail;
    unsigned long newFreq;
    head = tail = new ListNode; //  initializing the linkedlist pointers

    head->tree = new HuffmanNode(data[0].symbol,data[0].freq,data[0].runLen);

    for(int i=1;i<data.size();i++)
    {
        tail->next = new ListNode(tail,0);
        tail = tail->next;
        tail->tree = new HuffmanNode(data[i].symbol,data[i].freq,data[i].runLen);
    }

    while(head!=tail)
    {
        newFreq = head->tree->freq + head->next->tree->freq;

        for(p=tail;(p!=0 && p->tree->freq > newFreq);p=p->prev)
        {}
        newNode = new ListNode(p,p->next);

        p->next = newNode;
        if(p==tail)tail = newNode;
        else newNode->next->prev = newNode;

        newNode->tree = new HuffmanNode('#',newFreq,0,head->tree,head->next->tree);

        head = head->next->next;
        delete head->prev->prev;
        delete head->prev;
        head->prev = 0;
    }
    HuffmanTree = head->tree;
    //  delete head;    //  The memory pointed by head is deleted.
/**
    'head' contains the tree pointer object. If we free/delete the head pointer then the
    memory pointed by the head pointer is released and is given to the free pool
**/

//  Traversing the huffman tree
    HuffmanNode *travel;
    travel = HuffmanTree;
    cout<<"Travelling the huffman tree"<<endl;
    travel = travel->right;
    travel = travel->right;
    while(travel != NULL)
    {
        cout<<travel->symbol<<endl;
        travel = travel->left;
    }
}


void HuffmanCoding::checkBits(unsigned long &pack)  //  Function for checking the contents of the pack.
{
    unsigned long enc = pack;
    unsigned long mask = 1;
    HuffmanNode *p = HuffmanTree;
    vector<int> m;

    cout<<"\nInside checkBits()"<<endl;
    mask <<= 31;
    for(int i = 0; i < 32; i++)
    {
        if(enc & mask)
        {
            p = p->right;
            cout<<"1 ";
            //  m.push_back(1);
        }
        else
        {
            p = p->left;
            cout<<"0 ";
            //  m.push_back(0);
        }

        if(p->left == NULL && p->right == NULL) //  Reached the leaf node
        {
            //for(int j = 0; j < m.size(); j++)
                //cout<<m[i]<<" ";
            cout<<p->symbol<<endl;
            m.resize(0);
            p = HuffmanTree;    //  Go back to root again
            enc <<= 1;
        }
        else enc <<= 1;
    }

    enc = pack;
    for(int i = 0; i < 32; i++)
    {
        if(enc & mask) cout<<"1 ";
        else cout<<"0 ";
        enc <<= 1;
    }
//    for(int i = 0; i < m.s)
    cout<<"\n";
    //getch();
}

int solve()
{
	//  cout<<"Backend not implemented!"<<endl;
	cout<<"Inside solve. Now from here the compression proceduer begins"<<endl;
	//getch();
    char fname[30];
    HuffmanCoding Huffman;

    cout<<"\n\tEnter filename: ";
    //  cin>>fname;
	strcpy(fname,"d1.txt");
    ifstream fin(fname, ios::binary);
    if(fin.fail())
    {
        cout<<"cannot open the specified file"<<endl;
        return 5;
    }
	fstream fl("CsharpFile.txt", ios::ate|ios::in|ios::out);
	fl<<"From the shared library"<<endl;
    Huffman.compress(fname, fin);
    ifstream fdec("d1.en", ios::binary);
    if(fdec.fail())
    {
        cout<<"\n\tCannot decompress the file"<<endl;
        return 6;
    }
    Huffman.decompress("d1.en", fdec);
    return 10;
}

void allocate(char *s, string &str)
{
    for(int i = 0; i < strlen(s); i++)
        str += s[i];
}

int solveName(char *s, int len, int parity)
{
    HuffmanCoding Huffman;
    string str;
    fstream fout("Debugging.txt", ios::out);
    if(parity){
        allocate(s, str);
        int n = str.length();
        if(str[n-1]=='n' and str[n-2]=='e' and str[n-3]=='.'){
            fout<<"Trying to compress a compressed file\n";
            fout<<"Invalid operation\n";
            return 1;
        }

        ifstream fin(s, ios::binary);
        if(fin.fail()){
            fout<<"Cannot open file for compression\n";
            return 2;
        }

        Huffman.compress(s, fin);
        fout<<"Succesfully called compress() function\n";
        return 100;
    }
    else{
        allocate(s, str); int n = str.length();
        if(str.substr(n-3, 3) != ".en"){
            fout<<"Cannot decompress the file as the file extension is different\n";
            return 4;
        }

        ifstream fdec(s, ios::in | ios::binary);
        if(fdec.fail()){
            fout<<"Cannot open file for decompression\n";
            return 5;
        }
        Huffman.decompress(s, fdec);
        fout<<"Executed decompress function successfully\n";
        return 200;
    }
//    HuffmanCoding Huffman;
//    string str;
//    for(int i = 0; i < len; i++){
//        str += s[i];
//    }
//    fstream fout("Debugging.txt", ios::out);
//    ifstream fin(s, ios::binary);
//    if(fin.fail()){
//        fout<<"Cannot open the specified file\n";
//        return 5;
//    }
//    Huffman.compress(s, fin);
////    if(strchr(s, ','))
////        strcpy(strchr(s, '.')+1, ".en");
////    else strcat(s, ".en");
//    strcat(s, ".en");
//    str += ".en";
//    fout<<"string: "<<s<<"\n";
//    ifstream fdec(s, ios::in | ios::binary);  //  Not able to connect to the fileStream
//    if(fdec.fail()){
//        fout<<"Cannot decompress the file\n";
//        return 6;
//    }
//    Huffman.decompress(s, fdec);
//    return 10;
}

/*
int main()
{
    //  cout<<"Backend not implemented!"<<endl;

    char fname[30];
    HuffmanCoding Huffman;

    cout<<"\n\tEnter filename: ";
    cin>>fname;

    ifstream fin(fname, ios::binary);
    if(fin.fail())
    {
        cout<<"cannot open the specified file"<<endl;
        return 0;
    }

    Huffman.compress(fname, fin);
    ifstream fdec("d1.en", ios::binary);
    if(fdec.fail())
    {
        cout<<"\n\tCannot decompress the file"<<endl;
        return 0;
    }
    Huffman.decompress("d1.en", fdec);
    return 0;
}
*/





