#include <Arduino.h>
#include <List.h>

/*
    list<...type...> ...var-name...
*/

void creation()
{
    list<int> intlist;

    list<char> charlist;

    list<float> floatlist;

    list<String> Stringlist;

    struct Text
    {
        const char *content;
        void print()
        {
            Serial.println(content);
        }
    };
    list<Text> textlist;
}