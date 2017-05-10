#ifndef NODE_VALUE_H
#define NODE_VALUE_H


enum TokenType {
    TTPLUS = 0,
    TTMINUS,
    TTMULT,
    TTDIV,
    TTEQ,
    TTNEQ,
    TTGT,
    TTLT,
    TTGE,
    TTLE,
    TTAND,
    TTOR,
    TTNOT
};

class NodeValue {
public:
    virtual std::string getValue() = 0;
    virtual std::string getClassName() = 0;
    virtual ~NodeValue() {}
};

class StringValue : public NodeValue {
public:
    std::string * value;

    StringValue(std::string * val) {
        value = val;
    }

    std::string getValue() {
        return *value;
    }

    std::string getClassName() {
        return "StringValue";
    }
    ~StringValue() {
        delete value;
    }
};

class IntValue : public NodeValue {
public:
    int value;

    IntValue(int val) {
        value = val;
    }

    std::string getValue() {
        return std::to_string(value);
    }

    std::string getClassName() {
        return "IntValue";
    }
    ~IntValue() {

    }
};

class FloatValue : public NodeValue {
public:
    double value;

    FloatValue(double val) {
        value = val;
    }

    std::string getValue() {
        return std::to_string(value);
    }

    std::string getClassName() {
        return "FloatValue";
    }
    ~FloatValue() {

    }
};

class BoolValue : public NodeValue {
public:
    bool value;
    BoolValue(bool val) {
        value = val;
    }

    std::string getValue() {
        if (value) {
            return std::string("TRUE");
        }
        else {
            return std::string("FALSE");
        }
    }
    std::string getClassName() {
        return "BoolValue";
    }
    ~BoolValue() {

    }
};

class CharValue : public NodeValue {
public:
    char value;
    CharValue(char val) {
        value = val;
    }

    std::string getValue() {
        return std::string(1, value);
    }

    std::string getClassName() {
        return "CharValue";
    }
    ~CharValue() {

    }
};

class BinOp : public NodeValue {
public:
    TokenType tokenType;

    BinOp(TokenType tokenType) {
        this->tokenType = tokenType;
    }

    std::string getValue() {
        switch (tokenType) {
            case TTEQ:    return std::string("''=''");
            case TTNEQ:   return std::string("'!='");
            case TTGT:    return std::string("'>'");
            case TTLT:    return std::string("'<'");

            case TTGE:    return std::string("'>='");
            case TTLE:    return std::string("'<='");
            case TTAND:   return std::string("'and'");
            case TTOR:    return std::string("'or'");

            case TTPLUS:  return std::string("'+'");
            case TTMINUS: return std::string("'-'");
            case TTMULT:  return std::string("'*'");
            case TTDIV:   return std::string("'/'");

            default:     return std::string("Not defined");
        }
    }

    std::string getClassName() {
        return "BinOp";
    }
    ~BinOp () {

    }
};

class UnOp : public NodeValue  {
public:
    TokenType tokenType;

    UnOp(TokenType tokenType) {
        this->tokenType = tokenType;
    }

    std::string getValue() {
        switch (tokenType) {
            case TTNOT: return std::string("'not'");
            case TTMINUS: return std::string("'-u-'");
            default: return std::string("Not defined");
        }
    }

    std::string getClassName() {
        return "UnOp";
    }

    ~UnOp() {

    }
};

#endif
