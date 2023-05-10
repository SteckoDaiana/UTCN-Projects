package ro.tuc.ds2020.dtos;

import com.sun.istack.NotNull;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import org.springframework.hateoas.RepresentationModel;

import java.sql.Timestamp;
import java.util.UUID;

@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
public class MeasurementsDetailsDTO  extends RepresentationModel<MeasurementsDetailsDTO>
{

    private UUID id;
    Integer consumption;
    Timestamp timestamp;
    private String itemDescription;

}
