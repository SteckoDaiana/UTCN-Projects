package polynomialCalculator.model;

public class Monomial {
    Number coefficient;
    int power;

    public Monomial(Number coefficient, int power) {
        this.coefficient = coefficient;
        this.power = power;
    }

    public String toString(boolean asInt) {
        if(coefficient.floatValue() == 0){
            return "";
        }
        if(coefficient.floatValue() == 1.0 && power == 0)
            return coefToString(asInt);
        if(power == 0){
            return coefToString(asInt);
        }
        if(power == 1){
            return coefToString(asInt) + "x";
        }
        else{
            return coefToString(asInt) + "x^" + power;
        }
    }

    public String coefToString(boolean asInt){
        if(coefficient.floatValue() == 1.0 && power != 0)
            return "+";
        if(coefficient.floatValue() == -1.0 && power != 0)
            return "-";
        if(asInt){
            if(coefficient.intValue() > 0)
                return "+" + coefficient.intValue();
            else if( coefficient.floatValue() < 0)
                return Integer.toString(coefficient.intValue());
            else
                return "";
        }
        else {
            if(coefficient.floatValue() > 0)
                return "+" + coefficient.toString();
            else if( coefficient.floatValue() < 0)
                return coefficient.toString();
            else
                return "";
        }
    }

    public static Monomial Add(Monomial a, Monomial o){
        return new Monomial(a.coefficient.floatValue() + o.coefficient.floatValue(), a.power);
    }

    static Monomial Invert(Monomial a){
        return new Monomial(-a.coefficient.floatValue(), a.power);
    }

    static Monomial Multiply(Monomial a, Monomial b){
        return new Monomial(a.coefficient.floatValue() * b.coefficient.floatValue(),
                            a.power + b.power);
    }

    static Monomial Divide(Monomial a, Monomial b){
        return new Monomial(a.coefficient.floatValue() / b.coefficient.floatValue(),
                a.power - b.power);
    }

    static Monomial Differentiate(Monomial a){
        return new Monomial(a.power * a.coefficient.floatValue(), a.power - 1);
    }
    static Monomial Integrate(Monomial a){
        return new Monomial(a.coefficient.floatValue() / (a.power + 1), a.power + 1);
    }

    public Number getCoefficient() {
        return coefficient;
    }

    public void setCoefficient(Number coefficient) {
        this.coefficient = coefficient;
    }

    public int getPower() {
        return power;
    }

    public void setPower(int power) {
        this.power = power;
    }
}
