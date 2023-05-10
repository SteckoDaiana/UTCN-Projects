package ro.tuc.ds2020.dtos;

import com.sun.istack.NotNull;
import lombok.Getter;
import lombok.Setter;
import org.springframework.hateoas.RepresentationModel;
import ro.tuc.ds2020.entities.Role;

import java.util.UUID;

@Getter
@Setter


public class UserDetailsDTO extends RepresentationModel<UserDTO> {
    @NotNull
    private UUID id;
    @NotNull
    private String firstName;
    @NotNull
    private String lastName;
    @NotNull
    private String username;
    @NotNull
    private String password;
    @NotNull
    private Role role;


    public UserDetailsDTO() {

    }

    public UserDetailsDTO(UUID id, String firstName, String lastName, String username, String password, Role role) {
        this.id = id;
        this.firstName = firstName;
        this.lastName = lastName;
        this.username = username;
        this.password = password;
        this.role=role;
    }


}
