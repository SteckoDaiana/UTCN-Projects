package ro.tuc.ds2020.dtos.builders;


import ro.tuc.ds2020.dtos.UserDTO;
import ro.tuc.ds2020.dtos.UserDetailsDTO;
import ro.tuc.ds2020.entities.User;

public class UserBuilder {
    public UserBuilder() {
    }
    public static UserDTO toUserDTO(User user){
        return new UserDTO(user.getId(),user.getFirstName() ,user.getLastName(), user.getUsername(), user.getPassword(),  user.getRole());
    }
    public static UserDetailsDTO toUserDetailsDTO(User user){
        return new UserDetailsDTO(user.getId(), user.getFirstName() ,user.getLastName(), user.getUsername(), user.getPassword(), user.getRole());
    }
    public static User toEntity(UserDetailsDTO userDetailsDTO){
        return new User( userDetailsDTO.getFirstName() ,userDetailsDTO.getLastName(), userDetailsDTO.getUsername(), userDetailsDTO.getPassword(), userDetailsDTO.getRole());

    }
}
