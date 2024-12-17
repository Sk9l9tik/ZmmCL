#pragma once

#include <iostream>
#include <vector>
#include <string.h>

#include "INode.hh"


namespace AST {

	class Scope final : public IScope{
		std::vector<INode_ptr> nodes_; //< Vector of nodes in curent scope
		
		IScope* parent_; //< Pointer to parent scope

		var_table_t var_table; //< var table

	public:
		Scope(IScope* parent) : parent_(parent) {}

		IScope* reset_scope() override;

		int32_t calculate() override;

		void push(INode_ptr& node) override;
		
		~Scope() override;
	};


	/// @brief Class varible node
	class Var_Node final : INode{
		var_table_t::iterator position_;

	public:
		Var_Node(var_table_t::iterator pos) : position_(pos) {}

		std::string get_name() const { return position_->first; }

		int32_t calculate() override;

		var_table_t::iterator get_position() const { return position_; }

		void set_value(int32_t val);
	};


	class Operator_Node final : public INode{
		INode_ptr left_;
		INode_ptr right_;

		Operator_t operator_type_;

	public:
		Operator_Node(INode_ptr& lhs, Operator_t op_type, INode_ptr& rhs)
		: left_(lhs), right_(rhs), operator_type_(op_type) {}

		int32_t calculate() override;
	};


	class Assign_Node final : INode {
		using VNode_ptr = std::shared_ptr<Var_Node>;
		
		VNode_ptr destination_; //var to assign
		INode_ptr expression_; 

	public:
		Assign_Node(VNode_ptr& dest, INode_ptr& expr) : destination_(dest), expression_(expr) {}

		int32_t calculate() override;
	};


	class While_Node final : public INode{
		INode_ptr condition_;
		IScope_ptr scope_;

	public:
		While_Node(INode_ptr& cond, IScope_ptr& scope) : condition_(cond), scope_(scope) {}

		int32_t calculate() override;
	};


	class If_Node final : public INode {
		INode_ptr condition_;
		IScope_ptr if_scope_;


	public:
		If_Node(INode_ptr& cond, IScope_ptr& if_sc) : condition_(cond), if_scope_(if_sc) {}

		int32_t calculate() override;
	};


	class Print_Node final : public INode {
		INode_ptr expression_;

	public:
		Print_Node(INode_ptr& expr) : expression_(expr) {}

		int32_t calculate() override;
	};


	class Scan_Node final : public INode {
	public:
		Scan_Node() = default;

		int32_t calculate() override;
	};
}