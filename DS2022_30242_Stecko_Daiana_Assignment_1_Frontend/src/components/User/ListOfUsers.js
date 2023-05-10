import React, { Component } from "react";
import adminService from "../../services/adminService";

const adminUrl = "http://localhost:8080/person";

class ListOfUsers extends Component {
  constructor(props) {
    super(props);

    this.state = {
      useers: [],
    };
    this.addUser = this.addUser.bind(this);
    this.updateUser = this.updateUser.bind(this);
    this.deleteUser = this.deleteUser.bind(this);
  }

  addUser() {
    this.props.history.push(`${adminUrl}`);
  }
}
