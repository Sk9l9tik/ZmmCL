#pragma once 
#include <iostream>
#include <string>
#include <unordered_map>

namespace AST {


	class INode;
	class IScope;


	using INode_ptr = std::shared_ptr<INode>;
	using IScope_ptr = std::shared_ptr<IScope>;

	using var_table_t = std::unordered_map<std::string, int>; //< int replace to table members


	/// Node interface
	class INode {
	public:

		virtual int calculate() = 0;

		virtual ~INode() = default;
	};

	/// Scope interface
	class IScope : public INode{
	public:

		virtual void push(INode_ptr& node) = 0;

		virtual IScope* reset_scope() = 0;

	};

	/**
	* @enum Operator_t
	* @brief enum class with Operators
	*/
	enum class Operator_t {
		ASSIGN,

		ADD,
		SUB,
		MUL,
		MOD,
		
		GREATER,
		LESS,
		GR_EQ, // Greater than or equal
		LS_EQ, // Less than or equal 
		EQ,	// Eqaul
		NEQ, // Not equal

		AND,
		OR,
		NOT
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
	INode_ptr make_operator(INode_ptr& lhs, Operator_t op, INode_ptr& rhs);

	/**
	* @brief Make if node function
	* @param[in] cond shared ptr to condition node
	* @param[in] isc shared ptr to if scope
	* @return shared ptr to created Node
	*/
	INode_ptr make_if(INode_ptr& cond, IScope_ptr& isc);

	/**
	* @brief Make if else node function
	* @param[in] cond shared ptr to condition node
	* @param[in] isc shared ptr to if scope
	* @param[in] wsc shared ptr to else scope
	* @return shared ptr to created Node
	*/
	INode_ptr make_if_else(INode_ptr& cond, IScope_ptr& isc, IScope_ptr& esc);

	/**
	* @brief Make while node function
	* @param[in] cond shared ptr to condition node
	* @param[in] wsc shared ptr to while scope
	* @return shared ptr to created Node
	*/
	INode_ptr make_while(INode_ptr& cond, IScope_ptr& wsc);

	/**
	* @brief Make assigment node function
	* @param[in] var_name name of variable to assign
	* @param[in] expr shared ptr to expressiont to assign
	* @return shared ptr to created Node
	*/
	INode_ptr make_assign(std::string& var_name, INode_ptr& expr);

	/**
	* @brief Make print node function
	* @param[in] expr shared ptr to expressiont to print
	* @return shared ptr to created Node
	*/
	INode_ptr make_print(INode_ptr& expr);

	/**
	* @brief Make scan node function
	* @return shared ptr to created Node
	*/
	INode_ptr make_scan();

}
