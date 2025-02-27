#pragma once

#include <iostream>
#include <vector>
#include <string>


#include "INode.hh"

namespace AST {

	class Scope final : public IScope {
		friend IScope_ptr make_scope(IScope* par);

		std::vector<INode_ptr> nodes_; //< Vector of nodes in curent scope

		IScope* parent_; //< Pointer to parent scope

		var_table_t var_table_; //< var table

	public:
		//Scope() { parent_ = nullptr; }
		explicit Scope(IScope* parent) : parent_(parent) {}

		int32_t calculate() { for (auto&& node : nodes_) node->calculate(); return 0; }

		IScope* reset_scope() override { return parent_; }

		void push(const INode_ptr& node) override;

		iter_bool get_var(const std::string& name) override;
		bool check_var(const std::string& var_name) override;
		var_table_iterator insert(const std::string& var_name) override;
		iter_bool check_location(const std::string& var_name) override;

	public:
		~Scope() override {};

	private:
		var_table_iterator insert_var(const std::string& var_name);
	};

	/**
	* @class Const_Node
	* @brief class to constant value
	*/
	class Const_Node final : public INode {
		const int32_t value_;	//< Node value

	public:
		explicit Const_Node(int32_t val) : value_(val) {}

		int32_t calculate() override { return value_; };
	};


	/**
	* @class Var_Node
	* @brief Class varible node
	*/
	class Var_Node final : public INode {
    private:
        var_table_iterator position_;	//< position in var table

    public:
        Var_Node(const var_table_iterator& pos) : position_(pos) {}

        std::string get_name() const { return position_->first; }

        int32_t calculate() override { return position_->second; }

        var_table_iterator get_position() const { return position_; }

        void set_value(int32_t val) { position_->second = val; }
    };



	/**
	* @class Operator_Node
	* @brief Class operators Node
	*/
	class Operator_Node final : public INode {
		INode_ptr left_;	//< left operand 
		INode_ptr right_;	//< right operand
		Operator_t operator_type_;	//< operator

	public:
		Operator_Node(const INode_ptr& lhs, Operator_t op_type, const INode_ptr& rhs)
			: left_(lhs), right_(rhs), operator_type_(op_type) {}

		int32_t calculate() override;
	};

	/**
	* @class Unary_Operator_Node
	* @brief Class unary operators Node
	*/
	class Unary_Operator_Node final : public INode {
	private:
		INode_ptr operand_;	//< main operand
		Operator_t operator_type_;	//<operator

	public:
		Unary_Operator_Node(Operator_t op_type, const INode_ptr& operand)
			: operand_(operand), operator_type_(op_type) {}

		int32_t calculate() override;
	};

	/**
	* @class Assign_Node
	* @brief Class assign node
	*/
	class Assign_Node final : public INode {
		using VNode_ptr = std::shared_ptr<Var_Node>;

		VNode_ptr destination_; //< var to assign
		INode_ptr expression_;	//< exptression what assigned

	public:
		explicit Assign_Node(const VNode_ptr& dest, const INode_ptr& expr) : destination_(dest), expression_(expr) {}

		int32_t calculate() override;
	};

	/**
	* @class While_Node
	* @brief Class while cycle node
	*/
	class While_Node final : public INode {
	private:
		INode_ptr condition_;	//< cycle condition
		IScope_ptr scope_;		//< cycle scope

	public:
		While_Node(const INode_ptr& cond, const IScope_ptr& scope)
			: condition_(cond), scope_(scope) {}

		int32_t calculate() override;
	};

	/**
	* @class If_Node
	* @brief Class if condition node
	*/
	class If_Node final : public INode {
	private:
		INode_ptr condition_;	//< if condition
		IScope_ptr if_scope_;	//< if scope
		IScope_ptr else_scope_;	//else scope

	public:
		If_Node(const INode_ptr& cond, const IScope_ptr& if_sc, IScope_ptr el_sc = nullptr)
			: condition_(cond), if_scope_(if_sc), else_scope_(el_sc) {}

		int32_t calculate() override;
	};

	/**
	* @class Print_Node
	* @brief Class print node
	*/
	class Print_Node final : public INode {
	private:
		INode_ptr expression_;

	public:
		Print_Node(const INode_ptr& expr) : expression_(expr) {}

		int32_t calculate() override;
	};

	/**
	* @class Scan_Node
	* @brief Class scan node
	*/
	class Input_Node final : public INode {
	public:
		explicit Input_Node() = default;

		int32_t calculate() override;
	};
}