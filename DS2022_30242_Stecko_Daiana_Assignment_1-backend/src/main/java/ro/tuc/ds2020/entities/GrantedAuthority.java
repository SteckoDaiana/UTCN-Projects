package ro.tuc.ds2020.entities;


import java.io.Serializable;

public interface GrantedAuthority extends Serializable {
    String getAuthority();
}
