
#include "INode.hh"
#include "Node.hh"

namespace AST {

	IScope_ptr make_scope(IScope* par) {
		return std::make_shared<Scope>(par);
	}

	INode_ptr make_value(int32_t val) {
		return std::make_shared<Const_Node>(val);
	}

	INode_ptr make_operator(const INode_ptr& lhs, Operator_t op, const INode_ptr& rhs) {
		return std::make_shared<Operator_Node>(lhs, op, rhs);
	}

	INode_ptr make_unary(Operator_t op, const INode_ptr& rhs) {
		return std::make_shared<Unary_Operator_Node>(op, rhs);
	}

	INode_ptr make_if(const INode_ptr& cond, const IScope_ptr& isc) {
		return std::make_shared<If_Node>(cond, isc);
	}

	INode_ptr make_if_else(const INode_ptr& cond, const IScope_ptr& isc, const IScope_ptr& esc) {
		return std::make_shared<If_Node>(cond, isc);
	}

	INode_ptr make_while(const INode_ptr& cond, const IScope_ptr& wsc) {
		return std::make_shared<While_Node>(cond, wsc);
	}

	INode_ptr make_assign(std::string& var_name, const INode_ptr& expr) {
		auto iter = CURRENT_SCOPE->insert(var_name);
		auto var_ptr = std::make_shared<Var_Node>(iter);

		return std::make_shared<Assign_Node>(var_ptr, expr);
	}

	INode_ptr make_print(const INode_ptr& expr) {
		return std::make_shared<Print_Node>(expr);
	}

	INode_ptr make_input() {
		return std::make_shared<Input_Node>();
	}

	INode_ptr make_reference(const std::string& var_name) {
		iter_bool it_b = CURRENT_SCOPE->get_var(var_name);
		if (!it_b.second) {
			std::string wt = "Unknown variable '" + var_name + "'";
			throw std::runtime_error{ wt };
		}

		return std::make_shared<Var_Node>(it_b.first);
	}


	var_table_t::iterator Scope::insert_var(const std::string& var_name) {
		iter_bool iter = var_table_.emplace(var_name, 0);
		return iter.first;
	}

	iter_bool Scope::get_var(const std::string& var_name) {

		iter_bool it_b = check_location(var_name); //< check var in var_table

		if (it_b.second) {
			return it_b;
		}

		return it_b;
		//if not ??
	}

	void Scope::push(const INode_ptr& node) {
		nodes_.push_back(node);
	}

	iter_bool Scope::check_location(const std::string& var_name) {
		iter_bool it_b{};

		it_b.first = var_table_.find(var_name);
		it_b.second = (var_table_.end() != it_b.first);

		return it_b;
	}

	bool Scope::check_var(const std::string& var_name) {
		return get_var(var_name).second;
	}

	iter_bool Scope::insert(const std::string& var_name) {
		//if(check_var(var_name)) it need?
		iter_bool it_b = get_var(var_name);
		if (it_b.second) // check valid var
			it_b.first = insert_var(var_name);
		return it_b;
	}


	int32_t Operator_Node::calculate() {

		auto lhs = left_->calculate();
		auto rhs = right_->calculate();

		switch (operator_type_) {
		case Operator_t::ADD:
			return lhs + rhs;
		case Operator_t::SUB:
			return lhs - rhs;
		case Operator_t::MUL:
			return lhs * rhs;
		case Operator_t::DIV:
			if (rhs == 0) throw std::runtime_error("Divide by zero!\n");
			return lhs / rhs;
		case Operator_t::MOD:
			if (rhs == 0) throw std::runtime_error("Divide by zero!\n");
			return lhs % rhs;
		case Operator_t::GREATER:
			return static_cast<int>(lhs > rhs);
		case Operator_t::GR_EQ:
			return static_cast<int>(lhs >= rhs);
		case Operator_t::LESS:
			return static_cast<int>(lhs < rhs);
		case Operator_t::LS_EQ:
			return static_cast<int>(lhs >= rhs);
		case Operator_t::EQ:
			return static_cast<int>(lhs == rhs);
		case Operator_t::NEQ:
			return static_cast<int>(lhs != rhs);
		case Operator_t::AND:
			return static_cast<int>(lhs && rhs);
		case Operator_t::OR:
			return static_cast<int>(lhs || rhs);
		default:
			throw std::runtime_error("Unknown operator!\n");
		}
	}

	int32_t Unary_Operator_Node::calculate() {
		auto value = operand_->calculate();

		switch (operator_type_) {
		case Operator_t::NEG:
			return -value;
			break;
		case Operator_t::NOT:
			return static_cast<int>(!static_cast<bool>(value));
			break;
		default:
			throw std::runtime_error("Unknown operator!\n");
		}
	}

	int32_t Assign_Node::calculate() {
		auto expr = expression_->calculate();
		destination_->set_value(expr);
		return expr;
	}

	int32_t Print_Node::calculate() {
		auto expr = expression_->calculate();

		std::cout << expr << '\n';
	}

	int32_t Input_Node::calculate() {
		int32_t value;

		std::cin >> value;
		if (!std::cin.good())
			throw std::runtime_error("Invalid value int stdin!\n");
		return value;
	}

	int32_t While_Node::calculate() {
		return 0;
	}

	int32_t If_Node::calculate() {
		return 0;
	}
}