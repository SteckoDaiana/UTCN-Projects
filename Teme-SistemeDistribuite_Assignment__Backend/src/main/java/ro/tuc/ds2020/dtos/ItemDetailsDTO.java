package ro.tuc.ds2020.dtos;

import lombok.Getter;
import lombok.NonNull;
import lombok.Setter;
import org.springframework.hateoas.RepresentationModel;

import java.util.UUID;

@Getter
@Setter

public class ItemDetailsDTO extends RepresentationModel<ItemDTO> {
    @NonNull
    private UUID id_item;
    @NonNull
    private String description;
    @NonNull
    private String adress;
    @NonNull
    private Integer consumption;
    @NonNull
    private String username;

    public ItemDetailsDTO()  {

    }

    public ItemDetailsDTO(UUID id_item, String description, String adress, Integer consumption, String username) {
        this.id_item = id_item;
        this.description = description;
        this.adress = adress;
        this.consumption = consumption;
        this.username=username;
    }
}
