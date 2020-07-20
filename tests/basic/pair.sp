#include <shell>

Pair g_oPair = null;

public void main()
{
    g_oPair = new Pair(32, 4.0);
    print("first: "); printnum(g_oPair.First());
    print("second: "); printfloat(g_oPair.Second());
    delete g_oPair;

    print("\n");

    g_oPair = new Pair(3.0, 24);
    print("first: "); printfloat(g_oPair.First());
    print("second: "); printnum(g_oPair.Second());
    delete g_oPair;
}