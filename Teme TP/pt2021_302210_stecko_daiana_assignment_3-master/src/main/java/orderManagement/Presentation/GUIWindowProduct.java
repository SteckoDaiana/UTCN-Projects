package orderManagement.Presentation;

import orderManagement.BusinessLogic.Creator;
import orderManagement.BusinessLogic.Destroyer;
import orderManagement.BusinessLogic.Selector;
import orderManagement.BusinessLogic.Updater;
import orderManagement.Model.Product;
import javafx.geometry.Insets;
import javafx.scene.control.*;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;

public class GUIWindowProduct {
    private Button create = new Button("Create");
    private Button delete = new Button("Delete");
    private Button update = new Button("Update");
    private Button retrieve = new Button("Retrieve");
    private BorderPane root = new BorderPane();

    private TextField productName = new TextField();
    private TextField productSupplier = new TextField();
    private TextField productStock = new TextField();
    TableView<Product> productTableView = new TableView<>();

    public GUIWindowProduct(){
        HBox box = new HBox(5);
        box.getChildren().addAll( delete, retrieve);
        box.setPadding(new Insets(10,10,10,10));
        root.setTop(box);
        root.setCenter(productTableView);
        VBox form = new VBox(20);
        form.getChildren().addAll(
                new Label("Name") ,
                productName,
                new Label("Supplier"),
                productSupplier,
                new Label("Stock"),
                productStock,
                create,
                update);
        form.setPadding(new Insets(10, 10, 10,10));
        root.setRight(form);
        init();
    }

    private void init() {
        productTableView.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
        refreshTable();
        productTableView.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            if(newSelection != null){
                productName.setText(newSelection.getName());
                productSupplier.setText(newSelection.getSupplier());
                productStock.setText(Integer.toString(newSelection.getStock()));
            }
        });
        retrieve.setOnAction((e) -> refreshTable());
        create.setOnAction((e) ->{
            try {
                String name = productName.getText();
                String supplier = productSupplier.getText();
                int stock = Integer.parseInt(productStock.getText());
                Product p = new Product(-1, name, supplier, stock);
                Creator.run(Product.class, p);
                refreshTable();
            }
            catch (Exception ex){
                Alert a = new Alert(Alert.AlertType.ERROR);
                a.setContentText(ex.getMessage());
                a.show();
            }
        });
        update.setOnAction((e) ->{
            try {
                String name = productName.getText();
                String supplier = productSupplier.getText();
                int stock = Integer.parseInt(productStock.getText());
                Product p = new Product(productTableView.getSelectionModel().getSelectedItem().getId(), name, supplier, stock);
                Updater.run(Product.class, p);
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
                int id = productTableView.getSelectionModel().getSelectedItem().getId();
                Destroyer.run(Product.class, id);
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
        Selector.FillTable(Product.class, productTableView);
    }

    public BorderPane getRoot() {
        return root;
    }

    public void setRoot(BorderPane root) {
        this.root = root;
    }
}
