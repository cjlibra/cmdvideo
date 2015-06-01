package main

import (
	"bufio"
	"fmt"
	"github.com/ziutek/mymysql/mysql"
	_ "github.com/ziutek/mymysql/native" // Native engine
	"strings"
	//"io"
	//"io/ioutil"
	"log"
	"os"
	"os/exec"
	"time"
)

func checkError(error error) {
	if error != nil {
		panic("ERROR: " + error.Error()) // terminate program
	}
}
func opendb() mysql.Conn {

	db := mysql.New("tcp", "", "192.168.1.14:3306", "root", "anti410", "rfvid")

	err := db.Connect()
	if err != nil {
		panic(err)
	}
	return db

}

type RDSTAT struct {
	rdid     int
	ipreader string
	istat    int
}

var rdstat RDSTAT
var rdstats []RDSTAT

func getiprder() {
	for {
		db := opendb()

		res, err := db.Start("select * from reader")
		checkError(err)

		for {

			row, err := res.GetRow()
			checkError(err)

			if row == nil {
				// No more rows
				break
			}

			rdstat.rdid = row.Int(res.Map("id"))
			rdstat.ipreader = row.Str(res.Map("ipaddress"))
			rdstat.istat = 0
			iflag := 0
			for _, item := range rdstats {
				if item.ipreader == rdstat.ipreader {
					iflag = 1
					break
				}

			}
			if iflag == 0 {
				rdstats = append(rdstats, rdstat)
				go service(rdstat.ipreader)
				fmt.Println("++" + rdstat.ipreader)
			}

		}
		time.Sleep(time.Second * 15)
		fmt.Println(rdstats)

		db.Close()
	}
}
func main() {
	go getiprder()
	time.Sleep(time.Hour * 100)
}

func service(ip string) {
	lf, err := os.OpenFile("angel.txt"+ip, os.O_CREATE|os.O_RDWR|os.O_APPEND, 0600)
	if err != nil {
		os.Exit(1)
	}
	defer lf.Close()

	// 日志
	l := log.New(lf, "", os.O_APPEND)

	cmd := exec.Command("cmdvideo.exe", ip)
	//cmd.Stdout = os.Stdout

	//cmd.Stderr = os.Stderr
	stdout, _ := cmd.StdoutPipe()

	err = cmd.Start()
	if err != nil {
		l.Printf("%s 启动命令失败", time.Now().Format("2006-01-02 15:04:05"), err)

		time.Sleep(time.Second * 5)
		return
	}
	l.Printf("%s 进程启动", time.Now().Format("2006-01-02 15:04:05"), err)

	fileReader := bufio.NewReader(stdout)
	var rfidstr string
	for {
		w, _ := fileReader.ReadString('\n')

		tmp := strings.Split(w, " ")

		if len(w) > 30 {
			rfidstr = strings.Join(tmp, "")[12:24]

			//fmt.Printf(rfidstr + "\n")
			go InsertData(rfidstr, ip)
		}
	}

	err = cmd.Wait()
	l.Printf("%s 进程退出", time.Now().Format("2006-01-02 15:04:05"), err)

}

func InsertData(rfidstr string, ip string) {
	db := opendb()
	defer db.Close()

	stmt, err := db.Prepare("insert into monitorlog(begintime,cardid,readerid) select ? , card.id,reader.id from card inner join reader where reader.ipaddress = ? and card.UID = ? ")

	checkError(err)

	_, err = stmt.Run(time.Now().Format("2006-01-02 15:04:05"), ip, rfidstr)
	fmt.Println(time.Now().Format("2006-01-02 15:04:05") + " " + ip + " " + rfidstr)

	checkError(err)

}
