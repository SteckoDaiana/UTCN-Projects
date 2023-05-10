package ro.tuc.ds2020.dtos;

import lombok.Getter;
import lombok.Setter;
import org.springframework.hateoas.RepresentationModel;
import ro.tuc.ds2020.entities.Role;

import java.util.UUID;

@Getter
@Setter


public class UserDTO extends RepresentationModel<UserDTO>{

    private UUID id;
    private String firstName;
    private String lastName;
    private String username;
    private String password;
    private Integer enbled;
    private Role role;


    public  UserDTO () {

    }

    public  UserDTO (UUID id, String firstName, String lastName, String username, String password,  Role role) {
        this.id = id;
        this.firstName = firstName;
        this.lastName = lastName;
        this.username = username;
        this.password = password;
        this.role=role;
    }


    public UserDTO(UUID id, String username, Role role) {
    }
}
