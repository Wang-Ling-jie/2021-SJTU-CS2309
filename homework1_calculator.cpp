#include "std_lib_facilities.h"


class Token{
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
};


class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token
    void putback(Token t);    // put a Token back
private:
    bool full;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};

Token_stream::Token_stream()
    :full(false), buffer(0){}

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

Token Token_stream::get()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;

    switch (ch) {
    case ';':    // for "print"
    case '(': case ')': case '+': case '-': case '*': case '/':
        return Token(ch);        // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);         // put digit back into the input stream
        double val;
        cin >> val;              // read a floating-point number
        return Token('n', val);   // let 'n' represent "a number"
    }
    // please implement here!
    // handle unexpected character
    //
    default:error("unexpected character");
    }
}

Token_stream ts;        // provides get() and putback()
double expression();
double term();
double primary();

double expression()
{
    // please implement here!
    double left=term();
    while(true){
        Token t=ts.get();
        switch(t.kind){
            case '+':left+=term();break;
            case '-':left-=term();break;
            default:ts.putback(t);return left;
        }
    }
}

double term()
{
    // please implement here!
    double left=primary();
    while(true){
        Token t=ts.get();
        switch(t.kind){
            case '*':left*=primary();break;
            case '/':{
                double d=primary();
                if(d==0) error("divide by zero");
                left/=d;
                break;
            }
            default:ts.putback(t);return left;
        }
    }
}

double primary()
{
    // please implement here!
    bool isnegative=false;
    Token t=ts.get();
    if(t.kind=='-') {
        t=ts.get();
        isnegative=true;
    }
    switch(t.kind){
        case '(':{
            double d=expression();
            t=ts.get();
            if(t.kind!=')') error("unclosed parentheses");
            if(isnegative==false)
                return d;
            else return -d;
        }
        case 'n':
            if(isnegative==false)
                return t.value;
            else return -t.value;
    }
}


int main()
{
    double val = 0;
    try {
        while (cin) {
            Token t = ts.get();
            if (t.kind == ';')
            {
                cout << fixed;
                cout << setprecision(3) << val << '\n';
                break;
            }
            else
                ts.putback(t);
            val = expression();
        }
    }
    catch (exception& e) {
        cout << e.what() << '\n';
    }
}