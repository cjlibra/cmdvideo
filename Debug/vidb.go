package main

import (
	"bufio"
	"fmt"
	"github.com/ziutek/mymysql/mysql"
	//_ "github.com/ziutek/mymysql/native" // Native engine
	_ "github.com/ziutek/mymysql/thrsafe" // hreadsafe engine
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
		fmt.Println("ERROR: " + error.Error()) // terminate program
	}
}
func opendb() mysql.Conn {
here:
	db := mysql.New("tcp", "", "192.168.1.14:3306", "root", "anti410", "rfvid")

	err := db.Connect()
	if err != nil {
		//panic(err)
		time.Sleep(time.Second * 10)
		goto here
	}
	return db

}

type RDSTAT struct {
	rdid  int
	ipnvr string
	istat int
}

var rdstat RDSTAT
var rdstats []RDSTAT

func getiprder() {
	for {
		db1 := opendb()

		res, err := db1.Start("select * from nvr")
		checkError(err)

		for {

			row, err := res.GetRow()
			checkError(err)

			if row == nil {
				// No more rows
				break
			}

			rdstat.rdid = row.Int(res.Map("id"))
			rdstat.ipnvr = row.Str(res.Map("ipaddress"))
			rdstat.istat = row.Int(res.Map("state"))
			iflag := 0
			for _, item := range rdstats {
				if item.ipnvr == rdstat.ipnvr {
					iflag = 1
					break
				}

			}
			if iflag == 0 {
				rdstats = append(rdstats, rdstat)
				channel := 0
				for channel = 0; channel < 16; channel++ {
					go service(rdstat.ipnvr, channel)
					time.Sleep(time.Second * 5)
				}
				fmt.Println("++" + rdstat.ipnvr + " " + fmt.Sprintf("%d", channel))
			}

		}
		time.Sleep(time.Second * 15)
		fmt.Println(rdstats)

		db1.Close()
	}
}

func main() {

	go getiprder()
	time.Sleep(time.Hour * 100)
}

func service(ip string, channel int) {
	db := opendb()
	defer db.Close()

	lf, err := os.OpenFile("angel.txt"+ip+"-"+fmt.Sprintf("%d", channel), os.O_CREATE|os.O_RDWR|os.O_APPEND, 0600)
	if err != nil {
		os.Exit(1)
	}
	defer lf.Close()

	// 日志
	l := log.New(lf, "", os.O_APPEND)

	cmd := exec.Command("cmdvideo.exe", ip, "-1", fmt.Sprintf("%d", channel))
	//cmd.Stdout = os.Stdout

	//cmd.Stderr = os.Stderr
	stdout, _ := cmd.StdoutPipe()

	err = cmd.Start()
	if err != nil {
		l.Printf("%s 启动命令失败", time.Now().Format("2006-01-02 15:04:05"), err)

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
			go InsertData(db, rfidstr, ip, channel)
		}
	}

	err = cmd.Wait()
	l.Printf("%s 进程退出", time.Now().Format("2006-01-02 15:04:05"), err)

}

func InsertData(db mysql.Conn, rfidstr string, ip string, channel int) {

    err :=db.Ping()
	checkError(err)
	if err != nil {
	    return
	}
	
	stmt, err := db.Prepare("insert into monitorlog(begintime,endtime,cardid,readerid) select ? ,?, card.id,nrrelation.readerid from card inner join nrrelation  join nvr where nvr.ipaddress = ? and card.UID = ? and nrrelation.channelNum = ?")

	checkError(err)

	_, err = stmt.Run(time.Now().Format("2006-01-02 15:04:05"), time.Now().Format("2006-01-02 15:04:05"), ip, rfidstr, channel)
	fmt.Println(time.Now().Format("2006-01-02 15:04:05") + " " + ip + " " + rfidstr + " " + fmt.Sprintf("%d", channel))

	checkError(err)

}
