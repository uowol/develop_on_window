module.exports = (sequelize, DataTypes) => {
    let users = sequelize.define('users', {
        id: {
            type: DataTypes.INTEGER(11),
            primaryKey: true,
            autoIncrement: true,
            allowNull: false
        },
        name: {
            type: DataTypes.STRING(255),
            allowNull: false
        },
        age: {
            type: DataTypes.INTEGER(11),
            defaultValue: 25
        }
    }, {
        // tableName: 'users',
        // freezeTableName: false,
        // timestamps: false
    });
    // Before we use include for JOIN, we need to do this
    users.associate = models => {
        users.hasMany(models.boards); // default, same with under code
        // users.hasMany(models.boards, {foreignKey: 'userId'}); // default
        // users.hasMany(models.boards, {foreignKey: 'uId'}); // 1 : "n"
    };

    return users;
};