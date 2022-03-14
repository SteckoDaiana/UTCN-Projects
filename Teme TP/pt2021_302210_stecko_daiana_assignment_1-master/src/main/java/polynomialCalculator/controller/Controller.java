package polynomialCalculator.controller;

import javafx.util.Pair;
import polynomialCalculator.model.Polynomial;

public class Controller {

    public Polynomial add(String text, String text1) {
        Polynomial op1 = PolynomialParser.parse(text);
        Polynomial op2 = PolynomialParser.parse(text1);
        return Polynomial.Add(op1,op2);
    }

    public Polynomial subtract(String text, String text1) {
        Polynomial op1 = PolynomialParser.parse(text);
        Polynomial op2 = PolynomialParser.parse(text1);
        return Polynomial.Subtract(op1,op2);
    }

    public Polynomial multiply(String text, String text1) {
        Polynomial op1 = PolynomialParser.parse(text);
        Polynomial op2 = PolynomialParser.parse(text1);
        return Polynomial.Multiply(op1,op2);
    }

    public Pair<Polynomial, Polynomial> divide(String text, String text1) {
        Polynomial op1 = PolynomialParser.parse(text);
        Polynomial op2 = PolynomialParser.parse(text1);
        return Polynomial.Divide(op1,op2);
    }

    public Polynomial differentiate(String text) {
        Polynomial op1 = PolynomialParser.parse(text);
        return Polynomial.Differentiate(op1);
    }

    public Polynomial integrate(String text) {
        Polynomial op1 = PolynomialParser.parse(text);
        return Polynomial.Integrate(op1);
    }
}
