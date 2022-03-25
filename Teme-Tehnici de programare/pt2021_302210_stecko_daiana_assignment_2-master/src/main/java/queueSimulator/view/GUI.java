package queueSimulator.view;

import javafx.geometry.Insets;
import javafx.scene.control.*;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.text.Font;
import queueSimulator.model.Arguments;
import queueSimulator.controller.Simulator;

import java.util.Timer;

public class GUI {

    HBox controls = new HBox();

    Button start = new Button("START");
    Label clientsl = new Label("Clients:");
    TextField clients = new TextField();
    Label queuesl = new Label("Queues:");
    TextField queues = new TextField();
    Label timel = new Label("Time:");
    TextField time = new TextField();
    Label minATl = new Label("MinAT:");
    TextField minAT = new TextField();
    Label maxATl = new Label("MaxAT:");
    TextField maxAT = new TextField();
    Label minSTl = new Label("MinST:");
    TextField minST = new TextField();
    Label maxSTl = new Label("MaxST:");
    TextField maxST = new TextField();

    TextArea area = new TextArea();

    BorderPane root = new BorderPane();
    public BorderPane getRoot() {
        return root;
    }

    public GUI(){
        controls.setSpacing(10);
        controls.setPadding(new Insets(10,10,10,10));
        clients.setPrefWidth(50);
        queues.setPrefWidth(30);
        time.setPrefWidth(50);
        minAT.setPrefWidth(30);
        maxAT.setPrefWidth(30);
        minST.setPrefWidth(30);
        maxST.setPrefWidth(30);

        controls.getChildren().addAll(start, clientsl, clients, queuesl, queues,timel, time,
                minATl,minAT,maxATl, maxAT,minSTl, minST,maxSTl, maxST);

        area.setPadding(new Insets(10,10,10,10));
        area.setFont(new Font(20));
        area.setEditable(false);

        root.setTop(controls);
        root.setCenter(area);

        start.setOnAction(e -> {
            Arguments arg = getArguments();
            if(arg != null){
                Timer t = new Timer();
                Simulator sim = new Simulator(arg, t, this);
                t.schedule(sim, 0, 1000);
            }
        });

    }

    public void setArea(String text) {
        area.setText(text);
    }

    public Arguments getArguments() {
        Arguments arg = null;
        try{
            arg = new Arguments(
                    Integer.parseInt(clients.getText()),
                    Integer.parseInt(queues.getText()),
                    Integer.parseInt(minST.getText()),
                    Integer.parseInt(maxST.getText()),
                    Integer.parseInt(minAT.getText()),
                    Integer.parseInt(maxAT.getText()),
                    Integer.parseInt(time.getText())
            );
        }
        catch (Exception e){
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("ERROR");
            alert.setHeaderText("WRONG INPUT");
            alert.setContentText(e.getMessage());

            alert.showAndWait();

        }
        finally {
            return arg;
        }
    }
}
