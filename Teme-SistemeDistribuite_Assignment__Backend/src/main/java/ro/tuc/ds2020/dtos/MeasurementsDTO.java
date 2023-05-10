package ro.tuc.ds2020.dtos;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import org.hibernate.boot.model.source.spi.IdentifierSource;
import org.springframework.hateoas.RepresentationModel;

import java.sql.Timestamp;
import java.util.UUID;

@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
public class MeasurementsDTO extends RepresentationModel<MeasurementsDTO> {

    private UUID id;
    Integer consumption;
    Timestamp timestamp;
    private String itemDescription;



}
