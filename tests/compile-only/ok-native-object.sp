#include <shell>

methodmap CustomObject < Object
{
    public CustomObject()
    {
        return view_as<CustomObject>(null);
    }
}

CustomObject g_oTest = null;

public void main()
{
    g_oTest = new CustomObject();
    delete g_oTest;
}