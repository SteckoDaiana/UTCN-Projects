package orderManagement.DataAccess;

import javafx.scene.control.Alert;

import java.beans.PropertyDescriptor;
import java.lang.reflect.Field;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;

public class Querier<T> {
    private Class<T> t;

    public Querier(Class<T> t){
        this.t = t;
    }

    public ArrayList<T> all(){
        ArrayList<T> rez = new ArrayList<>();
        Connection connection = ConnectionFactory.getConnection();
        PreparedStatement statement = null;
        ResultSet set = null;
        try{
            statement = connection.prepareStatement("SELECT * FROM " + t.getSimpleName() + ";");
            set = statement.executeQuery();
            while (set.next()){
                T obj = t.newInstance();
                for(Field f : t.getDeclaredFields()){
                    Object o = set.getObject(f.getName());
                    PropertyDescriptor pd = new PropertyDescriptor(f.getName(), t);
                    pd.getWriteMethod().invoke(obj, o);
                }
                rez.add(obj);
            }
        }
        catch (Exception e){
            System.out.println(e);
            Alert a = new Alert(Alert.AlertType.ERROR);
            a.setContentText(e.getMessage());
            a.show();
        }
        finally {
            ConnectionFactory.close(connection);
            ConnectionFactory.close(statement);
            ConnectionFactory.close(set);
        }
        return rez;
    }

    public void insert(T obj) {
        Connection connection = ConnectionFactory.getConnection();
        PreparedStatement statement = null;
        ResultSet set = null;
        try{
            String s = buildSQLInsertQuery();
            statement = connection.prepareStatement(s);
            for(int f = 1; f < t.getDeclaredFields().length; ++f){
                PropertyDescriptor pd = new PropertyDescriptor(t.getDeclaredFields()[f].getName(), t);
                if(t.getDeclaredFields()[f].getType().equals(Integer.TYPE))
                    statement.setInt(f, (int)pd.getReadMethod().invoke(obj));
                else
                    statement.setString(f, pd.getReadMethod().invoke(obj).toString());
            }
            statement.execute();
        }
        catch (Exception e){
            e.printStackTrace();
            Alert a = new Alert(Alert.AlertType.ERROR);
            a.setContentText(e.getMessage());
            a.show();
        }
        finally {
            ConnectionFactory.close(connection);
            ConnectionFactory.close(statement);
            ConnectionFactory.close(set);
        }
    }

    private String buildSQLInsertQuery(){
        String s = "INSERT INTO " + t.getSimpleName() + " (";
        for(Field f: t.getDeclaredFields()){
            if(!f.getName().equals("id")){
                s += f.getName();
                s += ",";
            }
        }
        s = s.substring(0, s.length()-1);
        s += ") VALUES (";
        for(Field f: t.getDeclaredFields()){
            if(!f.getName().equals("id")){
                s += "?,";
            }
        }
        s = s.substring(0, s.length()-1);
        s += ")";
        return s;
    }

    public void update(T obj){
        Connection connection = ConnectionFactory.getConnection();
        PreparedStatement statement = null;
        ResultSet set = null;
        try{
            String s = buildSQLUpdateQuery();
            statement = connection.prepareStatement(s);
            int f;
            for(f = 1; f < t.getDeclaredFields().length; ++f){
                PropertyDescriptor pd = new PropertyDescriptor(t.getDeclaredFields()[f].getName(), t);
                statement.setString(f, pd.getReadMethod().invoke(obj).toString());//if int, do something else.
            }
            PropertyDescriptor pd = new PropertyDescriptor(t.getDeclaredFields()[0].getName(), t);
            statement.setInt(f, (int) pd.getReadMethod().invoke(obj));
            statement.execute();
        }
        catch (Exception e){
            System.out.println(e);
            Alert a = new Alert(Alert.AlertType.ERROR);
            a.setContentText(e.getMessage());
            a.show();
        }
        finally {
            ConnectionFactory.close(connection);
            ConnectionFactory.close(statement);
            ConnectionFactory.close(set);
        }
    }

    public void delete(int id){
        Connection connection = ConnectionFactory.getConnection();
        PreparedStatement statement = null;
        ResultSet set = null;
        try{
            String s = "DELETE FROM " + t.getSimpleName() + " WHERE id = ?";
            statement = connection.prepareStatement(s);
            statement.setInt(1, id);
            statement.execute();
        }
        catch (Exception e){
            System.out.println(e);
            Alert a = new Alert(Alert.AlertType.ERROR);
            a.setContentText(e.getMessage());
            a.show();
        }
        finally {
            ConnectionFactory.close(connection);
            ConnectionFactory.close(statement);
            ConnectionFactory.close(set);
        }
    }

    private String buildSQLUpdateQuery() {
        String s = "UPDATE " + t.getSimpleName() + " SET ";
        for(int f = 1; f < t.getDeclaredFields().length; ++f){
            s += t.getDeclaredFields()[f].getName() + " = ?,";
        }
        s = s.substring(0, s.length()-1);
        s += " WHERE id = ?";
        System.out.println(s);
        return s;
    }
}
