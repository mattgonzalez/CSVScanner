#pragma once

class ValueTreeTest : public ValueTree::Listener
{
public:
	ValueTreeTest(String name);

	virtual void valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged, const Identifier& property) override;

	virtual void valueTreeChildAdded(ValueTree& parentTree, ValueTree& childWhichHasBeenAdded) override;

	virtual void valueTreeChildRemoved(ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved) override;

	virtual void valueTreeChildOrderChanged(ValueTree& parentTreeWhoseChildrenHaveMoved) override;

	virtual void valueTreeParentChanged(ValueTree& treeWhoseParentHasChanged) override;

	String name;
	ValueTree tree;
};

