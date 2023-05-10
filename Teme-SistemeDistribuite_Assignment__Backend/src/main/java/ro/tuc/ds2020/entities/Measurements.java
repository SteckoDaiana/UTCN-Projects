package ro.tuc.ds2020.entities;

import lombok.*;
import org.hibernate.annotations.GenericGenerator;
import org.hibernate.annotations.Type;

import javax.persistence.*;
import java.io.Serializable;
import java.sql.Timestamp;
import java.util.UUID;

@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
@Builder
@Entity
@EqualsAndHashCode
@Table(name="measurements")
public class Measurements implements Serializable {

    private static  final long serialUID=1L;
    @Id
    @GeneratedValue(generator = "uuid2")
    @GenericGenerator(name = "uuid2", strategy = "uuid2")
    @Type(type = "uuid-binary")
    private UUID id;

    @ManyToOne
    @JoinColumn(name = "item_id")
    Item item;

    @Column(name="consumption", nullable = false)
    Integer consumption;

    @Column(name="timestamp",nullable = false)
    Timestamp timestamp;


    public Measurements(UUID id, Integer consumption, Timestamp timestamp) {
        this.id=id;
        this.consumption=consumption;
        this.timestamp=timestamp;
    }
}
