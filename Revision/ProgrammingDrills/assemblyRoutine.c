// Take a small C function -> compile -> read its
int myStrlen(const char *str)
{
    int count = 0;

    // Assign the str pointer to a pointer in order not to move the orginal pointer.
    const char *string = str;

    while (*string != '\0')
    {
        string++;
        count++;
    }
    return count;
}
