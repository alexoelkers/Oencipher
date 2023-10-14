char *stringXOR(char *a, char *b)

    void main()
{
}

char *stringXOR(char *a, char *b)
{
    char *output;
    char *cp = a;
    int len = 0;

    for (; *cp++ != '\0'; len++)
    {
    } // determine the length of the string

    int i = 0;
    while (i++ < len)
    {
        *output++ = *a++ ^ *b++;
    }
    *output++ = '\0';

    return output - (len + 1);
}