package polynomialCalculator.controller;

import polynomialCalculator.model.Monomial;
import polynomialCalculator.model.Polynomial;

import java.util.Comparator;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class PolynomialParser {
    public static Polynomial parse(String s){
        int maxim = 0;
        String exp="(?<mare>(?<n>[+-]?\\d+(?:\\.\\d+)?)?x*(?:\\^(?<p>\\d+))?)";
        Pattern pa = Pattern.compile(exp);
        Matcher m = pa.matcher(s);
        Polynomial poly = new Polynomial();
        int coef, pwr;
        while(m.find()){
            String n = m.group("n");
            String p = m.group("p");
            if(n == null && p == null && !m.group("mare").contains("x")){
                continue;
            }
            else if(n == null && p == null && m.group("mare").contains("x")){
                coef = 1;
                pwr = 1;
            }
            else if(n == null && p != null){
                coef = 1;
                pwr = Integer.parseInt(p);
            }
            else if(n != null && p == null){
                coef = Integer.parseInt(n);
                if(m.group("mare").contains("x"))
                    pwr = 1;
                else
                    pwr = 0;
            }
            else{
                coef = Integer.parseInt(n);
                pwr = Integer.parseInt(p);
            }
            if(pwr > maxim)
                maxim = pwr;
            Monomial mono = new Monomial(coef, pwr);
            poly.getMonomials().add(mono);
        }
        Polynomial newPoly = new Polynomial(maxim + 1);
        for(Monomial mono:poly.getMonomials()){
            Monomial ț = newPoly.getMonomials().get(mono.getPower());
            newPoly.getMonomials().set(mono.getPower(), Monomial.Add(ț, mono));
        }
        return newPoly;
    }
}
