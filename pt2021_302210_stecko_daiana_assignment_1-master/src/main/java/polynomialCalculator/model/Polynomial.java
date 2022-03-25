package polynomialCalculator.model;

import javafx.scene.control.Alert;
import javafx.util.Pair;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.stream.Collectors;

public class Polynomial {

    private ArrayList<Monomial> monomials;


    public Polynomial(){
        monomials = new ArrayList<>();
    }

    public Polynomial(int degree){
        monomials = new ArrayList<>();
        for(int i = 0; i < degree; ++i){
            monomials.add(new Monomial(0,i));
        }
    }

    public Polynomial(ArrayList<Monomial> ls){
        monomials = ls;
    }

    public Polynomial(int... X){
        monomials = new ArrayList<>();
        int i = 0;
        for(int x:X){
            monomials.add(new Monomial(x, i));
            i++;
        }
    }

    public static Polynomial Add(Polynomial op1, Polynomial op2) {
        if(op1.monomials.size() < op2.monomials.size())
        {
            Polynomial p = op1;
            op1 = op2;
            op2 = p;
        }
        Polynomial result = new Polynomial(Math.max(op1.monomials.size() + 1, op2.monomials.size() + 1));
        for(Monomial mon: op1.monomials){
            result.monomials.set(mon.getPower(), mon);
        }
        for(Monomial mon: op2.monomials){
            result.monomials.set(mon.getPower(), Monomial.Add(mon, result.monomials.get(mon.getPower())));
        }
        return result;
    }

    public String toString(boolean asInt) {
        StringBuilder stringBuilder = new StringBuilder();
        for (Monomial mon: monomials.stream().sorted(Comparator.comparingInt(Monomial::getPower).reversed()).collect(Collectors.toList())){
            stringBuilder.append(mon.toString(asInt));
        }
        if(stringBuilder.charAt(0) == '+')
            stringBuilder.delete(0,1);
        return stringBuilder.toString();
    }

    public static Polynomial Subtract(Polynomial op1, Polynomial op2) {
        op2.monomials = op2.monomials.stream().map(Monomial::Invert).collect(Collectors.toCollection(ArrayList::new));
        return Add(op1, op2);
    }

    public static Polynomial Multiply(Polynomial op1, Polynomial op2) {
        Polynomial result = new Polynomial(op1.monomials.size() + op2.monomials.size());
        for(Monomial mon: op1.monomials){
            for(Monomial mon2: op2.monomials){
                result.monomials.set(mon.getPower() + mon2.getPower(),
                        Monomial.Add(result.monomials.get(mon.getPower() + mon2.getPower()), Monomial.Multiply(mon, mon2)));

            }
        }
        return result;
    }

    public static Pair<Polynomial, Polynomial> Divide(Polynomial op1, Polynomial op2) {
        // op1 / op2 = result + rest
        Polynomial result = new Polynomial(op1.monomials.size());

        if(op1.monomials.size() < op2.monomials.size()){
            return new Pair<Polynomial, Polynomial>(result, op1);
        }
        if(op2.monomials.stream().allMatch(m -> m.coefficient.floatValue() == 0.0)){
            Alert a = new Alert(Alert.AlertType.ERROR);
            a.setContentText("DIVISION BY ZERO");
            a.show();
            return new Pair<>(new Polynomial(), new Polynomial());
        }
        while(helperSize(op1).power >= helperSize(op2).power){
            Monomial m = Monomial.Divide(
                    helperSize(op1),
                    helperSize(op2)
            );
            result.monomials.add(m);
            Polynomial newP = new Polynomial();
            newP.monomials.add(m);
            op1 = Polynomial.Subtract(op1, Polynomial.Multiply(op2, newP));
            System.out.println(op1.toString(false));
        }

        Polynomial newPoly = new Polynomial();
        for(Monomial mono: result.monomials){
            Monomial ț = newPoly.getMonomials().get(mono.getPower());
            newPoly.getMonomials().set(mono.getPower(), Monomial.Add(ț, mono));
        }

        return new Pair<Polynomial, Polynomial>(newPoly, op1);
    }

    static private Monomial helperSize(Polynomial p){
        return p.monomials.stream().max(Comparator.comparingInt(Monomial::getPower)).get();
    }

    public static Polynomial Differentiate(Polynomial op1) {
        return new Polynomial(
                op1.monomials.stream().map(Monomial::Differentiate).collect(Collectors.toCollection(ArrayList::new))
        );
    }

    public static Polynomial Integrate(Polynomial op1) {
        return new Polynomial(
                op1.monomials.stream().map(Monomial::Integrate).collect(Collectors.toCollection(ArrayList::new))
        );
    }

    public ArrayList<Monomial> getMonomials() {
        return monomials;
    }

    public void setMonomials(ArrayList<Monomial> monomials) {
        this.monomials = monomials;
    }
}
