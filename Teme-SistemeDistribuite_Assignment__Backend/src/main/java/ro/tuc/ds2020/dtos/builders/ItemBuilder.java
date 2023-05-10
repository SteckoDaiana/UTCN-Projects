package ro.tuc.ds2020.dtos.builders;

import ro.tuc.ds2020.dtos.ItemDTO;
import ro.tuc.ds2020.dtos.ItemDetailsDTO;
import ro.tuc.ds2020.entities.Item;

public class ItemBuilder {
    public ItemBuilder() {
    }
    public static ItemDTO toItemDTO(Item item){
        return new ItemDTO(item.getId(), item.getDescription(), item.getAdress(), item.getConsumption(),item.getUser().getUsername());
    }
    public static ItemDetailsDTO toItemDetailsDTO(Item item){
        return new ItemDetailsDTO(item.getId(),item.getDescription(),item.getAdress(),item.getConsumption(),item.getUser().getUsername());
    }
    public static Item toEntity(ItemDetailsDTO itemDetailsDTO){
        return new Item( itemDetailsDTO.getId_item(), itemDetailsDTO.getDescription(), itemDetailsDTO.getAdress(), itemDetailsDTO.getConsumption());
    }

}
