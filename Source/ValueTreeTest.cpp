#include "base.h"
#include "ValueTreeTest.h"

ValueTreeTest::ValueTreeTest(String name_) :
name(name_),
tree(name_ + "_tree")
{
}

void ValueTreeTest::valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
{
	DBG(name << " " << treeWhosePropertyHasChanged.getType().toString() << " " << property.toString());
}

void ValueTreeTest::valueTreeChildAdded(ValueTree& /*parentTree*/, ValueTree& /*childWhichHasBeenAdded*/)
{
}

void ValueTreeTest::valueTreeChildRemoved(ValueTree& /*parentTree*/, ValueTree& /*childWhichHasBeenRemoved*/)
{
}

void ValueTreeTest::valueTreeChildOrderChanged(ValueTree& /*parentTreeWhoseChildrenHaveMoved*/)
{
}

void ValueTreeTest::valueTreeParentChanged(ValueTree& /*treeWhoseParentHasChanged*/)
{
}



