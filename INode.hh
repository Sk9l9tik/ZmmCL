#pragma once 
#include <iostream>
#include <string>
#include <unordered_map>

namespace AST {

	//pre class defenition
	class INode;
	class IScope;


	using INode_ptr = std::shared_ptr<INode>;
	using IScope_ptr = std::shared_ptr<IScope>;
	using var_table_t = std::unordered_map<std::string, int>; //< int replace to table members
	using iter_bool = std::pair<var_table_t::iterator, bool>;

	//	using make_iscope_ptr = std::make_shared<IScope>()

	
	IScope* cur_scope = 0;;

	/// Node interface
	class INode {
	public:
		virtual int calculate() = 0; //<calculate function

		virtual ~INode() = default;
	};

	/// Scope interface
	class IScope : public INode{
	public:

		virtual void push(const INode_ptr& node) = 0;//< push to stack

		int32_t calculate() = 0;

		virtual IScope* reset_scope() = 0;

		virtual iter_bool get_var(const std::string& var_name) = 0;
		virtual bool check_var(const std::string& var_name) = 0;
		virtual iter_bool insert(const std::string& var_name) = 0;
		virtual iter_bool check_location(const std::string& var_name) = 0;
	};

	/**
	* @enum Operator_t
	* @brief enum class with Operators
	*/
	enum class Operator_t {
		ASSIGN,

		ADD,
		SUB,
		DIV,
		MUL,
		MOD,
		
		GREATER,
		LESS,
		GR_EQ, // Greater than or equal
		LS_EQ, // Less than or equal 
		EQ,	// Eqaul
		NEQ, // Not equal

		AND,
		OR
		//NOT
	};


	/**
	* @brief Create Scope fucntion
	* @param[in] Pointer to parent Scope
	* @return shared ptr to created Ncope
	*/
	IScope_ptr make_scope(IScope* par = nullptr);

	/**
	* @brief Make int value node function
	* @param[in] int value to node
	* @return shared ptr to created Node
	*/
	INode_ptr make_value(int32_t value);

	/**
	* @brief Make Operator_t node function
	* @param[in] lhs shared ptr to Left node Operator_t
	* @param[in] op Operator_t type
	* @param[in] rhs shared ptr to Right node Operator_t
	* @return shared ptr to created Node
	*/
	INode_ptr make_operator(const INode_ptr& lhs, Operator_t op, const INode_ptr& rhs);

	/**
	* @brief Make unary Operator_t node function
	* @param[in] op Operator_t type
	* @param[in] rhs shared ptr to Right node Operator_t
	* @return shared ptr to created Node
	*/
	INode_ptr make_unary_operator(Operator_t op, const INode_ptr& rhs;)
	/**
	* @brief Make if node function
	* @param[in] cond shared ptr to condition node
	* @param[in] isc shared ptr to if scope
	* @return shared ptr to created Node
	*/
	INode_ptr make_if(const INode_ptr& cond, const IScope_ptr& isc);

	/**
	* @brief Make if-else node function
	* @param[in] cond shared ptr to condition node
	* @param[in] isc shared ptr to if scope
	* @param[in] esc shared ptr to else scope
	* @return shared ptr to created Node
	*/
	INode_ptr make_if_else(const INode_ptr& cond, const IScope_ptr& isc, const IScope_ptr& esc);

	/**
	* @brief Make if else node function
	* @param[in] cond shared ptr to condition node
	* @param[in] isc shared ptr to if scope
	* @param[in] wsc shared ptr to else scope
	* @return shared ptr to created Node
	*/
	INode_ptr make_if_else(const INode_ptr& cond, const IScope_ptr& isc, const IScope_ptr& esc = nullptr);

	/**
	* @brief Make while node function
	* @param[in] cond shared ptr to condition node
	* @param[in] wsc shared ptr to while scope
	* @return shared ptr to created Node
	*/
	INode_ptr make_while(const INode_ptr& cond, const IScope_ptr& wsc);

	/**
	* @brief Make assigment node function
	* @param[in] var name of variable to assign
	* @param[in] expr shared ptr to expressiont to assign
	* @return shared ptr to created Node
	*/
	INode_ptr make_assign(std::string& var, const const INode_ptr& expr);

	/**
	* @brief Make print node function
	* @param[in] expr shared ptr to expressiont to print
	* @return shared ptr to created Node
	*/
	INode_ptr make_print(const INode_ptr& expr);

	/**
	* @brief Make scan node function
	* @return shared ptr to created Node
	*/
	INode_ptr make_scan();

}
