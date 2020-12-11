#include "vEB.h"

bool vEB::isMember(vEB V, int val)
{
    if ( (val == V.min) || (val == V.max) )
    {
        return true;
    }
    else if (V.universe == 2)
    {
        return false;
    }
    else
    {
        return isMember(V.cluster[high(val)], low(val));
    }
    
}

int vEB::successor(vEB V, int val)
{
    
}
