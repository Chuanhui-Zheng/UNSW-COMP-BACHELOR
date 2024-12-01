import {authLoginV1, authRegisterV1} from './auth.js'
import {clearV1} from './other.js'
const error = {error: 'error'};
describe('test for error authLoginV1 only',() =>{
    test.each([
        {input_email: '130@qq.com', input_password: '123456'},
        {input_email: '2870@qq.com', input_password: '123456'},
        {input_email: '123@qq.com', input_password: '199996'},
    ])('Should match error, cannot find user with email since the user list is empty',({input_email, input_password}) =>{
        clearV1();
        expect(authLoginV1(input_email, input_password)).toStrictEqual(error);
    })

    test.each([
        {input_email: '130@qq.com', input_password: '123456'},
        {input_email: '2870@qq.com', input_password: '123456'},
        {input_email: '123@qq.com', input_password: '199996'},
    ])('Should match error, cannot find user with the given email',({input_email, input_password}) =>{
        clearV1();
        const not_same_email = '189029@qq.com';
        authRegisterV1(not_same_email, input_password, 'Yuyun', 'Zhou');
        expect(authLoginV1(input_email, input_password)).toStrictEqual(error);
    })

    test.each([
        {input_email: '130@qq.com', input_password: '123456'},
        {input_email: '2870@qq.com', input_password: '123456'},
        {input_email: '123@qq.com', input_password: '199996'},
    ])('Should match error, email is matched but the password is wrong',({input_email, input_password}) =>{
        clearV1();
        const not_correct_password = 'Wrong Password';
        authRegisterV1(input_email, input_password, 'Yuyun', 'Zhou');
        expect(authLoginV1(input_email, not_correct_password)).toStrictEqual(error);
    })
});

describe('test for error return situation of authRegisterV1 only, should all return error',() =>{
    test.each([
        {input_email: '130@qq.com', input_password: '12345',
         input_first_name: 'Yuyun', input_last_name: 'Zhou'},

         {input_email: '130@qq.com', input_password: '145',
         input_first_name: 'Yuyun', input_last_name: 'Zhou'},

         {input_email: '130@qq.com', input_password: '1',
         input_first_name: 'Yuyun', input_last_name: 'Zhou'},

         {input_email: '130@qq.com', input_password: '',
         input_first_name: 'Yuyun', input_last_name: 'Zhou'},
    ])('Pathword is too short.',({input_email, input_password, input_first_name, input_last_name}) =>{
        clearV1();
        expect(authRegisterV1(input_email, input_password, input_first_name, input_last_name)).toStrictEqual(error);
    })

    test.each([
        {input_email: '130@qq.com', input_password: '12345678',
         input_first_name: 'lkjhgfdsaqwertyuiopzxcvbnm, kuytre kuytrdcvblkjhgfdsaqwertyuiopzxcvbnm, kuytre kuytrdcvb',
        input_last_name: 'lkjhgfdsaqwertg hgfdxcv jhflkjhgfdsaqwertg hgfdxcv jhflkjhgfdsaqwertg hgfdxcv jhf'},

         {input_email: '130@qq.com', input_password: '12345678',
         input_first_name: 'lkjhgfdsaqwertyuiopzxcvbnm, kuytre kuytrdcvblkjhgfdsaqwertyuiopzxcvbnm, kuytre kuytrdcvb',
        input_last_name: 'Zhou'},

         {input_email: '130@qq.com', input_password: '12345678',
         input_first_name: 'Yuyun',
        input_last_name: 'lkjhgfdsaqwertyuiopzxcvbnm, kuytre kuytrdcvblkjhgfdsaqwertyuiopzxcvbnm, kuytre kuytrdcvb'},
         
         {input_email: '130@qq.com', input_password: '12345678',
         input_first_name: '', input_last_name: ''},

         {input_email: '130@qq.com', input_password: '12345678',
         input_first_name: '', input_last_name: 'Yuyun'},

         {input_email: '130@qq.com', input_password: '12345678',
         input_first_name: 'Zhou', input_last_name: ''},
    ])('Invalid name length',({input_email, input_password, input_first_name, input_last_name}) =>{
        clearV1();
        expect(authRegisterV1(input_email, input_password, input_first_name, input_last_name)).toStrictEqual(error);
    })

    test.each([
        {input_email: '130qq.com', input_password: '12345678',
         input_first_name: 'Yuyun', input_last_name: 'Zhou'},

         {input_email: 'qq.com', input_password: '12345678',
         input_first_name: 'Yuyun', input_last_name: 'Zhou'},

         {input_email: '130121', input_password: '12345678',
         input_first_name: 'Yuyun', input_last_name: 'Zhou'},
         
         {input_email: '130qqcom', input_password: '12345678',
         input_first_name: 'Yuyun', input_last_name: 'Zhou'},
    ])('Not valid email',({input_email, input_password, input_first_name, input_last_name}) =>{
        clearV1();
        expect(authRegisterV1(input_email, input_password, input_first_name, input_last_name)).toStrictEqual(error);
    })

    test.each([
        {input_email: '13820@q.com', input_password: '12345678',
         input_first_name: 'abbbs', input_last_name: 'amnss'},

         {input_email: '1298230@a1.com', input_password: '12345678',
         input_first_name: 'kjdbe', input_last_name: 'sxns'},

         {input_email: '11asi30@q.com', input_password: '12345678',
         input_first_name: 'kwhx', input_last_name: 'dmds'},
         
         {input_email: '1301ygxv@n.com', input_password: '12345678',
         input_first_name: 'ksjx', input_last_name: 'kjxidus'},
    ])('Email is used by another user',({input_email, input_password, input_first_name, input_last_name}) =>{
        clearV1();
        authRegisterV1(input_email,input_password,input_first_name, input_last_name);
        const a = authRegisterV1(input_email,'Another_Password','Delph', 'Me');
        expect(a).toStrictEqual(error);
    })
});

clearV1();

describe('mixed test for authRegisterV1 and authLoginV1',() =>{
    test.each([
        {input_email: '1301@qq.com', input_password: '1234590',
         input_first_name: 'Teacher', input_last_name: 'Hayden'},
         {input_email: '1302@qq.com', input_password: 'asdfghjkl',
         input_first_name: 'Another_teacher', input_last_name: 'Tam'},
         {input_email: '1303@qq.com', input_password: 'ygvfrdxsq',
         input_first_name: 'Me', input_last_name: 'Delph'},
         {input_email: '130au3@qq.com', input_password: 'ysjhgxvgvfrdxsq',
         input_first_name: 'Good', input_last_name: 'Luck'},
         {input_email: '130axhui3@qq.com', input_password: 'ysjwxejijohdhgxvgvfrdxsq',
         input_first_name: 'Goodks', input_last_name: 'Lucka8iu'},
    ])('Mixed authRegisterV1 and authLoginV1 test, their returned id should be same and NOT error.',
    ({input_email, input_password, input_first_name, input_last_name}) =>{
        const a = authRegisterV1(input_email,input_password,input_first_name, input_last_name);
        const b = authLoginV1(input_email, input_password);
        expect(a).toStrictEqual(b);
    })
});