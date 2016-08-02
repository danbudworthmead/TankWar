#include "Node.h"
Node::Node()
{
}

Node::~Node()
{
	for (Node* child : children_)
		delete child;
	children_.clear();
}

//\=================================================================================
//\ Returns the nodes parent
//\=================================================================================
Node* Node::GetParent() const
{
	return parent_;
}

//\=================================================================================
//\ Set the nodes parent and returns false if there is already a parent
//\=================================================================================
bool Node::SetParent(Node* a_parent)
{
	if (parent_)
	{
		return false;
	}
	parent_ = a_parent;
	children_.push_back(this);
	return true;
}

//\=================================================================================
//\ Add a child node to this node
//\=================================================================================
void Node::AddChild(Node* a_child)
{
	if (a_child->GetParent())
	{
	}
	else
	{
		children_.push_back(a_child);
		a_child->parent_ = this;
	}
}

//\=================================================================================
//\ Start drawing this node and it's children
//\=================================================================================
void Node::StartDrawing()
{
	if (sprite_ != 0)
		UG::DrawSprite(sprite_);
	for (Node* child : children_)
		child->StartDrawing();
}

//\=================================================================================
//\ Stop drawing this node and it's children
//\=================================================================================
void Node::StopDrawing()
{
	if (sprite_ != 0)
		UG::StopDrawingSprite(sprite_);
	for (Node* child : children_)
		child->StopDrawing();
}

//\=================================================================================
//\ Get a child from this node
//\=================================================================================
Node* Node::GetChild(unsigned a_num)
{
	return children_[a_num];
}