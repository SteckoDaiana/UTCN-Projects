package orderManagement.Presentation;

import orderManagement.BusinessLogic.Creator;
import orderManagement.BusinessLogic.Selector;
import orderManagement.BusinessLogic.Updater;
import orderManagement.Model.Client;
import orderManagement.Model.Product;
import orderManagement.Model.ProductOrder;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.geometry.Insets;
import javafx.scene.control.*;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;

import java.util.ArrayList;

public class GUIWindowOrder {
    private Button create = new Button("Create");

    private BorderPane root = new BorderPane();

    TableView<ProductOrder> orderTableView = new TableView<>();

    private TextField quantity = new TextField();

    private ComboBox<String> clients = new ComboBox<>();
    private ComboBox<String> products = new ComboBox<>();
    private ObservableList<String> clientObservableList = null;
    private ObservableList<String> productObservableList = null;
    private ArrayList<Client>  clientArrayList;
    private ArrayList<Product>  productArrayList;

    public BorderPane getRoot(){
        return root;
    }

    public GUIWindowOrder(){
        productObservableList = FXCollections.observableArrayList();
        clientObservableList = FXCollections.observableArrayList();
        root.setCenter(orderTableView);
        VBox form = new VBox(20);
        form.getChildren().addAll(
                new Label("Client:"),
                clients,
                new Label("Product:"),
                products,
                new Label("Quantity:"),
                quantity,
                create
        );
        form.setPadding(new Insets(10,10,10,10));
        root.setRight(form);
        init();
    }

    private void init() {
        orderTableView.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
        refreshTable();
        refreshData();
        create.setOnAction((e) -> {
            try {
                String client = clients.getSelectionModel().getSelectedItem();
                String product = products.getSelectionModel().getSelectedItem();
                int quantity = Integer.parseInt(this.quantity.getText());
                for(Product p: productArrayList){
                    if(p.getName().equals(product)){
                        if(quantity > p.getStock()){
                            throw new Exception("Quantity exeeds stock for " + product);
                        }
                        else{
                            p.setStock(p.getStock() - quantity);
                            Updater.run(Product.class, p);
                        }
                    }
                }
                ProductOrder order = new ProductOrder(0,client, product, quantity);
                Creator.run(ProductOrder.class, order);
                refreshTable();
                //deschizi un fisier -> desktop
                //scrii in el deltaliile orderului.
            }
            catch (Exception ex){
                Alert a = new Alert(Alert.AlertType.ERROR);
                a.setContentText(ex.getMessage());
                a.show();
            }
        });

    }

    public void refreshData() {
        clientArrayList = Selector.selectAll(Client.class);
        productArrayList = Selector.selectAll(Product.class);
        clientObservableList.clear();
        for(Client c: clientArrayList){
            clientObservableList.add(c.getName());
        }
        clients.setItems(clientObservableList);
        productObservableList.clear();
        for (Product p: productArrayList) {
            productObservableList.add(p.getName());
        }
        products.setItems(productObservableList);

    }

    private void refreshTable() {
        Selector.FillTable(ProductOrder.class, orderTableView);
    }

}
