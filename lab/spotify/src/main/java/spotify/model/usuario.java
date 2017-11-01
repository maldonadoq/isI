package spotify.model;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name = "usuarios")
public class usuario{
	@Id
	@Column(length = 16)
	public String Id;
	
	@Column(length = 64, nullable = false)
	public String Nombre;
	
	@Column(name = "ap_pat", length = 64, nullable = false)
	public String ApellidoPaterno;
	
	@Column(name = "ap_mat", length = 64)
	public String ApellidoMaterno;
	
	@Column(length = 64, nullable = false)
	public String Correo;

	public String getId() {
		return Id;
	}

	public void setId(String id) {
		Id = id;
	}

	public String getNombre() {
		return Nombre;
	}

	public void setNombre(String nombre) {
		Nombre = nombre;
	}

	public String getApellidoPaterno() {
		return ApellidoPaterno;
	}

	public void setApellidoPaterno(String apellidoPaterno) {
		ApellidoPaterno = apellidoPaterno;
	}

	public String getApellidoMaterno() {
		return ApellidoMaterno;
	}

	public void setApellidoMaterno(String apellidoMaterno) {
		ApellidoMaterno = apellidoMaterno;
	}

	public String getCorreo() {
		return Correo;
	}

	public void setCorreo(String correo) {
		Correo = correo;
	}
}
