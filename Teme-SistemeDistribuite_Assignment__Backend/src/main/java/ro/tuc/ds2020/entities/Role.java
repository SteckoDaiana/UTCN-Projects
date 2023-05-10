package ro.tuc.ds2020.entities;

public enum Role implements GrantedAuthority{

    ADMINISTRATOR,
    CLIENT;


    @Override
    public String getAuthority(){return this.name();}
}
