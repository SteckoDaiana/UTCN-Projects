package orderManagement.Presentation;

import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;

public class GUI {

    TabPane root = new TabPane();

    public TabPane getRoot() {
        return root;
    }
    private GUIWindowProduct products = new GUIWindowProduct();
    private GUIWindowClient clients = new GUIWindowClient();
    private GUIWindowOrder orders = new GUIWindowOrder();

    public GUI(){
        root.setTabClosingPolicy(TabPane.TabClosingPolicy.UNAVAILABLE);

        Tab clientsTab = new Tab("Clients");
        clientsTab.setContent(clients.getRoot());
        Tab productTab = new Tab("Products");
        productTab.setContent(products.getRoot());
        Tab orderTab = new Tab("Orders");
        orderTab.setContent(orders.getRoot());

        root.getSelectionModel().selectedItemProperty().addListener((obs, t, t2) ->{
            if(t2.equals(orderTab)){
                orders.refreshData();
            }
            if(t2.equals(productTab)){
                products.refreshTable();
            }
        });
        root.getTabs().addAll(clientsTab, productTab, orderTab);
    }
}
