package queueSimulator;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;
import queueSimulator.view.GUI;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{

        GUI gui = new GUI();
        primaryStage.setScene(new Scene(gui.getRoot(), 800, 500));
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
