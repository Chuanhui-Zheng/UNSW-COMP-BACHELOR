import {userProfileV1} from './users.js';
import {authRegisterV1, authLoginV1} from './auth.js'
import {clearV1} from './other.js'

const users = [
    {email: 'haydens@gmail.com', password: 'helloworld', nameFirst: 'Hayden', nameLast: 'Smith',},
    {email: 'timmy@gmail.com', password: 'password', nameFirst: 'Timmy', nameLast: 'White',},
    {email: 'jsnow@gmail.com', password: 'winter"s coming', nameFirst: 'Jone', nameLast: 'Snow',},
];

const ERROR = {
    error: 'error',
};

describe('BlackBox Testing: Pass cases (userProfileV1)', ()=>{
    let au_id;
    beforeEach(()=>{
        clearV1();
        au_id = authRegisterV1('aksora@yahoo.com', 'metoosweet', 'Ethan', 'Sun').authUserId;
        expect(authLoginV1('aksora@yahoo.com', 'metoosweet').authUserId).toStrictEqual(au_id);
    });

    test.each(users)('Test: regular cases', ({ email, password, nameFirst, nameLast }) => {
        let u_id = authRegisterV1(email, password, nameFirst, nameLast).authUserId;
        expect(authLoginV1(email, password).authUserId).toStrictEqual(u_id);
        expect(userProfileV1(u_id, u_id)).toStrictEqual(
            expect.objectContaining({
                user : {
                'uId' : u_id,
                'email' : email,
                'handleStr' : expect.any(String),
                'nameFirst' : nameFirst,
                'nameLast' : nameLast,
            }})
        );
    })

    test.each(users)('Test: searching theirselves" profiles', ({ email, password, nameFirst, nameLast }) => {
        let u_id = authRegisterV1(email, password, nameFirst, nameLast).authUserId;
        expect(authLoginV1(email, password).authUserId).toStrictEqual(u_id);
        expect(userProfileV1(u_id, u_id)).toStrictEqual(
            expect.objectContaining({
                user : {
                'uId' : u_id,
                'email' : email,
                'handleStr' : expect.any(String),
                'nameFirst' : nameFirst,
                'nameLast' : nameLast,
            }})
        );
    })
});

describe('BlackBox Testing: Fail cases (userProfileV1)', ()=>{
    let au_id;
    beforeEach(()=>{
        clearV1();
        au_id = authRegisterV1('aksora@yahoo.com', 'metoosweet', 'Ethan', 'Sun').authUserId;
        expect( authLoginV1('aksora@yahoo.com', 'metoosweet').authUserId ).toStrictEqual(au_id);
    });

    test.each(users)('Test: invalid autherised userId', ({ email, password, nameFirst, nameLast }) => {
        let u_id = authRegisterV1(email, password, nameFirst, nameLast).authUserId;
        expect(authLoginV1(email, password).authUserId).toStrictEqual(u_id);
        expect(userProfileV1(au_id-100, u_id)).toStrictEqual(ERROR);
        expect(userProfileV1((au_id+10)*2, u_id)).toStrictEqual(ERROR);
    })

    test.each(users)('Test: negative autherised userId', ({ email, password, nameFirst, nameLast }) => {
        let u_id = authRegisterV1(email, password, nameFirst, nameLast).authUserId;
        expect(authLoginV1(email, password).authUserId).toStrictEqual(u_id);
        expect(userProfileV1(-(au_id+100), u_id)).toStrictEqual(ERROR);
        expect(userProfileV1((au_id+10)*-2, u_id)).toStrictEqual(ERROR);
    })

    test.each(users)('Test: invalid userId', ({ email, password, nameFirst, nameLast }) => {
        let u_id = authRegisterV1(email, password, nameFirst, nameLast).authUserId;
        expect(authLoginV1(email, password).authUserId).toStrictEqual(u_id);
        expect(userProfileV1(au_id, (u_id-100))).toStrictEqual(ERROR);
        expect(userProfileV1(au_id, (au_id+10)*2)).toStrictEqual(ERROR);
    })

    test.each(users)('Test: negative userId', ({ email, password, nameFirst, nameLast }) => {
        let u_id = authRegisterV1(email, password, nameFirst, nameLast).authUserId;
        expect(authLoginV1(email, password).authUserId).toStrictEqual(u_id);
        expect(userProfileV1(au_id, -(u_id+100))).toStrictEqual(ERROR);
        expect(userProfileV1(au_id, (au_id+10)*-2)).toStrictEqual(ERROR);
    })
});
