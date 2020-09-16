# Socket Sample (Windows)

This is a Linux-based socket sample.
Use it to explore client and server communication.

- What is the sequence on the server side and client side?
- What can happen in parallel? Across sides and within each side?

# Next step

Currently, the server accepts the connection
and waits for data from the client.

Change the server and the client,
for the server to respond with a 'certificate' first.
The certificate is in the form of a structure

```C
struct Certificate
{
    char name[38];
    unsigned int hash;
};
```
