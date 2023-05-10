package ro.tuc.ds2020.dtos;

import lombok.Getter;
import lombok.Setter;
import org.springframework.hateoas.RepresentationModel;

import java.util.UUID;

@Getter
@Setter

public class ItemDTO extends RepresentationModel<ItemDTO>{

    private UUID id_item;
    private String description;
    private String adress;
    private Integer consumption;
    private String username;

    public ItemDTO() {

    }

    public ItemDTO(UUID id_item, String description, String adress, Integer consumption, String username) {
        this.id_item = id_item;
        this.description = description;
        this.adress = adress;
        this.consumption = consumption;
        this.username=username;
    }

}
