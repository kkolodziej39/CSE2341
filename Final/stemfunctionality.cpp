#include "stemfunctionality.h"
#include "english_stem.h"
#include <iostream>
#include <string>

//using namespace std;

StemFunctionality::StemFunctionality()
{

}


void StemFunctionality::stemWord(string & input)
{
    //the word to be stemmed
    std::wstring word(L"transportation");
    /*create an instance of a "english_stem" class. The template argument for the
    stemmers are the type of std::basic_string that you are trying to stem, by default
    std::wstring (Unicode strings). As long as the char type of your basic_string is wchar_t,
    then you can use any type of basic_string. This is to say, if your basic_string has a custom
    char_traits or allocator, then just specify it in your template argument to the stemmer. For example:
    typedef std::basic_string<wchar_t, myTraits, myAllocator> myString;
    myString word(L"documentation");
    stemming::english_stem<myString> StemEnglish;
    StemEnglish(word);*/
    stemming::english_stem<> StemEnglish;
    //std::wcout << L"(English) Original text:\t" << word.c_str() << std::endl;
    //the "english_stem" has its operator() overloaded, so you can
    //treat your class instance like it's a function.  In this case,
    //pass in the std::wstring to be stemmed.  Note that this alters
    //the original std::wstring, so when the call is done the string will
    //be stemmed.
    //StemEnglish(word);
    //now the variable "word" should equal "document"
    //std::wcout << L"(English) Stemmed text:\t" << word.c_str() << std::endl;
    //try a similar word that should have the same stem
    //word = L"documenting";
    //std::wcout << L"(English) Original text:\t" << word.c_str() << std::endl;
    //StemEnglish(word);
    //now the variable "word" should equal "document"
    //std::wcout << L"(English) Stemmed text:\t" << word.c_str() << std::endl;

    /*if you are using std::string (ANSI strings) then convert it to a temporary
    wchar_t buffer, assign that to a std::wstring, and then stem that.*/
    //std::string ANSIWord("documentation");
    wchar_t* UnicodeTextBuffer = new wchar_t[input.length()+1];
    std::wmemset(UnicodeTextBuffer, 0, input.length()+1);
    std::mbstowcs(UnicodeTextBuffer, input.c_str(), input.length());
    word = UnicodeTextBuffer;
    StemEnglish(word);
    //now the variable "word" should equal "document"
    //std::wcout << L"\nDemonstrating the stemming of an ANSI string:\n";
    //std::wcout << L"(English) Original text:\t" << ANSIWord.c_str() << std::endl;
    //std::wcout << L"(English) Stemmed text:\t" << word.c_str() << std::endl;

    //Used this resource to convert back to string
    //https://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string
    std::string s( word.begin(), word.end() );
    input.assign(s);



}
