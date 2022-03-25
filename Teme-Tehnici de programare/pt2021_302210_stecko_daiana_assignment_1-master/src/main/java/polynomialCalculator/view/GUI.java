package polynomialCalculator.view;

import javafx.collections.FXCollections;
import javafx.geometry.Insets;
import javafx.scene.Parent;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.util.Pair;
import polynomialCalculator.controller.Controller;
import polynomialCalculator.model.Polynomial;

public class GUI {

    protected BorderPane root;

    ComboBox<String> comboBox = new ComboBox<>();
    Button compute = new Button("Compute!");
    TextField operator1 = new TextField();
    TextField operator2 = new TextField();
    TextField result = new TextField();
    TextField remainder = new TextField();

    Controller controller = new Controller();


    public GUI(){
        root = new BorderPane();
        comboBox.getItems().addAll(
                "add",
                "subtract",
                "multiply",
                "divide",
                "differentiate",
                "integrate"
        );
        comboBox.getSelectionModel().selectFirst();
        HBox h = new HBox(5);
        h.setPadding(new Insets(10,10,10,10));
        h.getChildren().addAll(comboBox, compute);
        root.setTop(h);
        VBox v = new VBox(10);
        operator1.setPromptText("First polynomial");
        operator2.setPromptText("Second polynomial");
        result.setPromptText("Result");
        result.setEditable(false);
        remainder.setEditable(false);
        remainder.setPromptText("Remainder");
        v.getChildren().addAll(operator1, operator2, result, remainder);
        v.setPadding(new Insets(10,10,10,10));
        root.setCenter(v);
        compute.setOnAction(e -> ComputeResult());
    }

    private void ComputeResult() {
        String operation = comboBox.getSelectionModel().getSelectedItem();
        switch (operation) {
            case "add":
                Polynomial p1 = controller.add(operator1.getText(), operator2.getText());
                result.setText(p1.toString(true));
                break;
            case "subtract":
                Polynomial p2 = controller.subtract(operator1.getText(), operator2.getText());
                result.setText(p2.toString(true));
                break;
            case "multiply":
                Polynomial p3 = controller.multiply(operator1.getText(), operator2.getText());
                result.setText(p3.toString(true));
                break;
            case "divide":
                Pair<Polynomial, Polynomial> p4 = controller.divide(operator1.getText(), operator2.getText());
                result.setText(p4.getKey().toString(false));
                remainder.setText(p4.getValue().toString(false));
                break;
            case "differentiate":
                Polynomial p5 = controller.differentiate(operator1.getText());
                result.setText(p5.toString(true));
                break;
            case "integrate":
                Polynomial p6 = controller.integrate(operator1.getText());
                result.setText(p6.toString(false));
                break;
        }
    }

    public Parent getRoot() {
        return root;
    }
}
