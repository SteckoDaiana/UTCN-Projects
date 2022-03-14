package orderManagement.Presentation;

import orderManagement.BusinessLogic.Creator;
import orderManagement.BusinessLogic.Destroyer;
import orderManagement.BusinessLogic.Selector;
import orderManagement.BusinessLogic.Updater;
import orderManagement.Model.Client;
import javafx.geometry.Insets;
import javafx.scene.control.*;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;

public class GUIWindowClient {

    private Button create = new Button("Create");
    private Button delete = new Button("Delete");
    private Button update = new Button("Update");
    private Button retrieve = new Button("Retrieve");

    private BorderPane root = new BorderPane();

    private TextField clientName = new TextField();
    private TextField clientEmail = new TextField();
    private TextField clientAddress = new TextField();

    TableView<Client> clientTableView = new TableView<>();

    public GUIWindowClient(){
        HBox box = new HBox(5);
        box.getChildren().addAll( delete, retrieve);
        box.setPadding(new Insets(10,10,10,10));
        root.setTop(box);
        root.setCenter(clientTableView);
        VBox form = new VBox(20);
        form.getChildren().addAll(new Label("Name") ,clientName, new Label("Email"),
                clientEmail,new Label("Address"), clientAddress, create, update);
        form.setPadding(new Insets(10, 10, 10,10));
        root.setRight(form);
        init();
    }

    private void init() {
        clientTableView.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
        refreshTable();
        clientTableView.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            if(newSelection != null){
                clientName.setText(newSelection.getName());
                clientEmail.setText(newSelection.getEmail());
                clientAddress.setText(newSelection.getAddress());
            }
        });
        retrieve.setOnAction((e) -> refreshTable());
        create.setOnAction((e) ->{
            try {
                String name = clientName.getText();
                String email = clientEmail.getText();
                String address = clientAddress.getText();
                Client c = new Client(-1, name, email, address);
                Creator.run(Client.class, c);
                refreshTable();
            }
            catch (Exception ex){
                Alert a = new Alert(Alert.AlertType.ERROR);
                a.setContentText(ex.getMessage());
                a.show();
            }
        });
        update.setOnAction((e) -> {
            try {
                String name = clientName.getText();
                String email = clientEmail.getText();
                String address = clientAddress.getText();
                Client c = new Client(clientTableView.getSelectionModel().getSelectedItem().getId(), name, email, address);
                Updater.run(Client.class, c);
                refreshTable();
            }
            catch (Exception ex){
                Alert a = new Alert(Alert.AlertType.ERROR);
                a.setContentText(ex.getMessage());
                a.show();
            }
        });
        delete.setOnAction((e) -> {
            try {
                int id = clientTableView.getSelectionModel().getSelectedItem().getId();
                Destroyer.run(Client.class, id);
                refreshTable();
            }
            catch (Exception ex){
                Alert a = new Alert(Alert.AlertType.ERROR);
                a.setContentText(ex.getMessage());
                a.show();
            }
        });
    }

    public void refreshTable() {
        Selector.FillTable(Client.class, clientTableView);
    }

    public BorderPane getRoot() {
        return root;
    }

    public void setRoot(BorderPane root) {
        this.root = root;
    }
}
