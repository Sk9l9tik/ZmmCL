#pragma once

#include <iostream>
#include <vector>
#include <string.h>

#include "INode.hh"

namespace AST {

	class Scope final : public IScope{
		std::vector<INode_ptr> nodes_; //< Vector of nodes in curent scope
		
		IScope* parent_; //< Pointer to parent scope

		var_table_t var_table_; //< var table

	public:
		Scope(IScope* parent) : parent_(parent) {}

		int32_t calculate() { return 0; }

		IScope* reset_scope() override { return parent_; }

		void push(const INode_ptr& node) override;
		
		iter_bool get_var(const std::string& name) override;
		bool check_var(const std::string& var_name) override;
		iter_bool insert(const std::string& var_name) override;
		//iter_bool check_location(const std::string& var_name) override;
	public:
		~Scope() override {};

	private:
		var_table_t::iterator insert_var(const std::string& var_name);
	};


	class Const_Node final : public INode {
		const int32_t value_;

	public:
		Const_Node(int32_t val) : value_(val) {}

		int32_t calculate() override { return value_; } ;
	};

	/// @brief Class varible node
	class Var_Node final : INode{
		var_table_t::iterator position_;

	public:
		Var_Node(var_table_t::iterator pos) : position_(pos) {}

		std::string get_name() const { return position_->first; }

		int32_t calculate() override { return position_->second; }

		var_table_t::iterator get_position() const { return position_; }

		void set_value(int32_t val) { position_->second = val; }
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


	class Assign_Node final : public INode {
		using VNode_ptr = std::shared_ptr<Var_Node>;
		
		VNode_ptr destination_; //var to assign
		INode_ptr expression_; 

	public:
		Assign_Node(const VNode_ptr& dest, const INode_ptr& expr) : destination_(dest), expression_(expr) {}

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
		IScope_ptr else_scope_;

	public:
		If_Node(INode_ptr& cond, IScope_ptr& if_sc, IScope_ptr el_sc = nullptr) : condition_(cond), if_scope_(if_sc), else_scope_{ el_sc } {}

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