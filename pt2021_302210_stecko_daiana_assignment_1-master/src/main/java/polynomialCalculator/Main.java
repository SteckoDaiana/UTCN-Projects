package polynomialCalculator;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;
import polynomialCalculator.view.GUI;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage){
        GUI gui = new GUI();
        primaryStage.setScene(new Scene(gui.getRoot(), 400, 300));
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
