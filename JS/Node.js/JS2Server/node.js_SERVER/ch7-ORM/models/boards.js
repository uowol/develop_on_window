module.exports = (sequelize, DataTypes) => {
    let boards = sequelize.define('boards', {
        id: {
            type: DataTypes.INTEGER(11),
            primaryKey: true,
            autoIncrement: true,
            allowNull: false
        },
        title: {
            type: DataTypes.STRING(255)
        },
        content:{
            type: DataTypes.TEXT
        }
        // userId: {
        //     type: DataTypes.INTEGER(11),
        //     allowNull: false
        // }
    }, {
        // tableName: 'boards',
        // freezeTableName: false,
        // timestamps: false
    });
    boards.associate = models => {
        boards.belongsTo(models.users); // default, same with under code
        // boards.belongsTo(models.users, {foreignKey: 'userId', targetKey: 'id'}); // default 
        // boards.belongsTo(models.users, {foreignKey: 'uId', targetKey: 'id'}); // "1" : n
    };

    return boards;
};