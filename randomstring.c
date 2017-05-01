Taking this one step at a time:

The first function to consider was inputChar. From the source code, we need random characters that include brackets and a blank space.
This can be accoplished using the ASCII data table between the values of 0 and 127. So, we need to use random to get us a value
between these numbers, and return that value as a char. Using rand() and modulating by 128 will give us a random integer between
0 and 127. Casting that as a characer will convert it from integer to ASCII character.

Likewise, with inputString, we need to gather 5 different random characters in a string (ie array), and make sure that 5 character string is
terminated by a '\0' for an end-of-string terminator. Thus, I run through a loop like the previous function,
assign each random character to an array value, tac on the '\0' as the final character, and pass a reference back to the calling main
procedure. This should produce the error, although the liklihood is VERY low.