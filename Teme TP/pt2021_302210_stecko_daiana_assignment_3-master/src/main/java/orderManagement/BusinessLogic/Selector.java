package orderManagement.BusinessLogic;


import orderManagement.DataAccess.Querier;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;

import java.lang.reflect.Field;
import java.util.ArrayList;

public class Selector {

    static public <T>  void FillTable(Class<T> t, TableView<T> table){
        table.getColumns().clear();
        for(Field f: t.getDeclaredFields()){
            TableColumn<T,String> col = new TableColumn<>(f.getName());
            col.setCellValueFactory(
                    new PropertyValueFactory<T,String>(f.getName())
            );
            table.getColumns().add(col);
        }
        Querier<T> q = new Querier<>(t);
        ObservableList<T> l = FXCollections.observableArrayList(q.all());
        table.setItems(l);
    }
    static public <T> ArrayList<T> selectAll(Class<T> t){
        Querier<T> q = new Querier<>(t);
        return q.all();
    }
}
