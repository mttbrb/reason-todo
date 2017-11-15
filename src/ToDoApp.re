let component = ReasonReact.statelessComponent("ToDoApp");

let make = (_children) => {
    ...component,
    render: (_self) =>
      <div className="app">
        <div className="title"> (ReasonReact.stringToElement("What to do")) </div>
        <div className="items"> (ReasonReact.stringToElement("Nothing")) </div>
      </div>
};